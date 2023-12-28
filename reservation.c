#include "reservation.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

// Create a reservation
Reservation createReservation(int code, Date dateA, Date dateD, int roomNumber, Client client) {
    Reservation r;
    r.code = code;
    r.arrivalDate = dateA;
    r.departureDate = dateD;
    r.roomNumber = roomNumber;
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

// Add a reservation to the list
ReservationList *addReservationToList(ReservationList *head, Reservation reservation) {
    ReservationList *newNode = malloc(sizeof(ReservationList));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->reservation = reservation;
    newNode->next = head;
    return newNode;
}

// Display reservations
void displayReservations(ReservationList *head) {
    ReservationList *current = head;
    while (current != NULL) {
        Reservation r = current->reservation;
        // Display logic for reservation 'r'
        current = current->next;
    }
}

// Read header from file
Header readHeader(FILE *file) {
    Header header;
    fread(&header, sizeof(Header), 1, file);
    return header;
}

// Write header to file
void writeHeader(char *filename, Header header) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&header, sizeof(Header), 1, file);
    fclose(file);
}

// Open a file
FILE *openFile(char *filename, char mode) {
    FILE *file = fopen(filename, mode == 'r' ? "rb" : "wb");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

// Transform reservation
Reservation transformReservation(Reservation reservation) {
    Reservation transformed = reservation;
    // Transform the reservation as needed
    return transformed;
}

// Convert logical block to physical block
ReservationBlock convertToPhysicalBlock(ReservationBlock logicalBlock) {
    ReservationBlock physicalBlock;
    // Conversion logic
    return physicalBlock;
}

// Load reservation from file
ReservationBlock loadReservation(char *filename, int blockNumber) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    ReservationBlock block;
    fseek(file, blockNumber * sizeof(ReservationBlock), SEEK_SET);
    fread(&block, sizeof(ReservationBlock), 1, file);
    fclose(file);
    return block;
}

// Insert reservation and update index
IndexList *insertReservation(char *filename, Reservation reservation, IndexList *indexList) {
    // Insertion logic
    // Update index
    return indexList;
}

// Convert block to list
ReservationList *blockToList(ReservationBlock block) {
    ReservationList *list = NULL;
    // Conversion logic
    return list;
}
