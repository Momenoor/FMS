#include "reservation.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

// Create a reservation
Reservation createReservation(int code, Date dateA, Date dateD, int flightNumber, Client client) {
    Reservation r;
    r.code = code;
    r.arrivalDate = dateA;
    r.departureDate = dateD;
    r.flightNumber = flightNumber;
    r.client = client;
    return r;
}

// Create a date
Date createDate(int day, int month, int year) {
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}


// Function to add a reservation to a linked list
ReservationNode* addReservationToList(ReservationNode *head, Reservation c, IndexList **indexList) {
    ReservationNode *newNode = (ReservationNode *)malloc(sizeof(ReservationNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    newNode->reservation = c;
    newNode->next = head;

    int newPosition = 0;
    // Update the index list
    if (*indexList != NULL) {
        // Increment the index of existing reservations
        IndexList *currentIdx = *indexList;
        while (currentIdx != NULL) {
            currentIdx->item.address.i += 1;
            currentIdx = currentIdx->next;
        }
    }
    *indexList = addIndex(c.code, newPosition, 0, *indexList);

    return newNode;
}


// Function to display a reservation's information
// Function to display a reservation's information
void displayReservation(Reservation r) {
    char client = displayClient(r.client);
    printf("Code: %d, Arrival Date: %s, Departure Date %s, Flight Number: %s, Client: $s\n", r.code, r.arrivalDate, r.departureDate, r.flightNumber, client);
}

// Function to display all reservations in the list
void displayAllReservations(ReservationNode *head) {
    ReservationNode *current = head;
    while (current != NULL) {
        displayReservation(current->reservation);
        current = current->next;
    }
}
// Function to search for a reservation by code in the linked list
Reservation* searchReservation(int code, ReservationNode *head, IndexList *indexList) {
    int position = -1;
    IndexList *currentIdx = indexList;
    while (currentIdx != NULL) {
        if (currentIdx->item.key == code) {
            position = currentIdx->item.address.i;
            break;
        }
        currentIdx = currentIdx->next;
    }

    if (position == -1) {
        return NULL; // Reservation not found
    }

    ReservationNode *current = head;
    for (int i = 0; current != NULL && i < position; i++) {
        current = current->next;
    }

    return current != NULL ? &(current->reservation) : NULL;
}

void modifyReservationInFile(int code, Date newArrivalDate, Date newDepartureDate, int newFlightNumber, Client newClient, const char *reservationFilename, IndexList *indexList) {
    long position = getReservationPositionFromFile(code, indexList);
    if (position == -1) {
        printf("Reservation not found.\n");
        return;
    }

    FILE *file = fopen(reservationFilename, "r+b"); // Open file for reading and writing
    if (file == NULL) {
        perror("Error opening reservation file");
        return;
    }

    Reservation reservation;
    fseek(file, position, SEEK_SET);
    fread(&reservation, sizeof(Reservation), 1, file);

    // Modify the reservation's details
    reservation.arrivalDate = newArrivalDate;
    reservation.departureDate = newDepartureDate;
    reservation.flightNumber = newFlightNumber;
    reservation.client = newClient;

    fseek(file, position, SEEK_SET); // Go back to the reservation's position
    fwrite(&reservation, sizeof(Reservation), 1, file); // Write the updated reservation

    fclose(file);
}

// Function to delete a reservation from the list and return the position of the deleted reservation
void deleteReservationFromFile(int code, const char *reservationFilename, IndexList **indexList) {
    long position = getReservationPositionFromFile(code, *indexList);
    if (position == -1) {
        printf("Reservation not found.\n");
        return;
    }

    FILE *file = fopen(reservationFilename, "r+b");
    if (file == NULL) {
        perror("Error opening reservation file");
        return;
    }

    Reservation reservation;
    fseek(file, position, SEEK_SET);
    fread(&reservation, sizeof(Reservation), 1, file);

    // Mark the reservation as deleted (assuming there's a 'deleted' flag in the Reservation structure)

    fseek(file, position, SEEK_SET);
    fwrite(&reservation, sizeof(Reservation), 1, file);

    fclose(file);

    // Update the index list
    deleteReservationIndexByPosition(indexList, position);
}

#include "reservation.h" // Include necessary headers

void modifyReservation(ReservationNode *head, int code, Date arrivalDate, Date departureDate, int flightNumber, Client client) {
    ReservationNode *current = head;

    while (current != NULL) {
        if (current->reservation.code == code) {
            // Modify the reservation's information
            current->reservation.arrivalDate = arrivalDate;
            current->reservation.departureDate = departureDate;
            current->reservation.flightNumber = flightNumber;
            current->reservation.client = client;
            return; // Exit the function once modified
        }
        current = current->next;
    }

    // If the reservation with the given code was not found
    printf("Reservation with code %d not found.\n", code);
}


void deleteReservation(ReservationNode **head, int code, IndexList **indexList) {
    ReservationNode *current = *head;
    ReservationNode *prev = NULL;

    while (current != NULL) {
        if (current->reservation.code == code) {
            // Found the client to delete
            if (prev == NULL) {
                *head = current->next; // Update the head if deleting the first node
            } else {
                prev->next = current->next; // Update the previous node's next pointer
            }
            free(current);

            // Update the index list
            return; // Reservation deleted, exit the function
        }
        prev = current;
        current = current->next;
    }
    printf("Reservation with code %d not found.\n", code);
}

void deleteReservationIndexByPosition(IndexList **indexList, int position) {
    if (indexList == NULL || *indexList == NULL) {
        return; // Empty list or invalid input
    }

    IndexList *current = *indexList;
    IndexList *prev = NULL;

    while (current != NULL) {
        if (current->item.address.i == position) {
            if (prev == NULL) {
                *indexList = current->next; // Delete the head of the index list
            } else {
                prev->next = current->next; // Delete from middle or end
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    // Update the positions of subsequent indexes
    current = (prev == NULL) ? *indexList : prev->next;
    while (current != NULL) {
        current->item.address.i -= 1; // Decrement the position
        current = current->next;
    }
}
void saveReservationToFile(Reservation c, const char *filename) {
    FILE *file = fopen(filename, "ab"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fwrite(&c, sizeof(Reservation), 1, file); // Write the reservation to the file
    fclose(file); // Close the file
}
long getReservationPositionFromFile(int reservationCode, const char *indexFilename) {
    FILE *indexFile = fopen(indexFilename, "rb");
    if (indexFile == NULL) {
        perror("Error opening index file");
        return -1;
    }

    Index indexEntry;
    while (fread(&indexEntry, sizeof(Index), 1, indexFile)) {
        if (indexEntry.key == reservationCode) {
            fclose(indexFile);
            return indexEntry.address.i;  // Assuming 'i' holds the file offset
        }
    }

    fclose(indexFile);
    return -1;  // Reservation not found
}
Reservation getReservationFromFile(long position, const char *reservationFilename) {
    FILE *reservationFile = fopen(reservationFilename, "rb");
    if (reservationFile == NULL) {
        perror("Error opening reservation file");
        return (Reservation){0};  // Return an empty reservation structure
    }

    Reservation reservation;
    fseek(reservationFile, position, SEEK_SET);
    fread(&reservation, sizeof(Reservation), 1, reservationFile);
    fclose(reservationFile);

    return reservation;
}
