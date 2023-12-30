#include <stdio.h>
#include "client.h"         // Contains client-related functions and structures
#include "reservation.h"    // Contains reservation-related functions and structures
#include "struct.h"
#include "index.h"
// Contains additional structure definitions

int fileExists(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}

int main()
{
    int choice;
    ClientNode* clientList = NULL;
    ReservationNode* reservationList = NULL;
    IndexList* indexList = NULL;
    const char* reservationFilename = "reservations.txt";
    const char* clientFilename = "clients.txt";
    const char* indexFilename = "index.txt";
    // Check if reservation file exists, create if not
    if (!fileExists(reservationFilename))
    {
        FILE* file = fopen(reservationFilename, "w");
        if (file)
        {
            fclose(file);
            printf("Created empty reservation file.\n");
        }
        else
        {
            perror("Error creating reservation file");
            return 1; // Exit with an error code
        }
    }

    // Check if client file exists, create if not
    if (!fileExists(clientFilename))
    {
        FILE* file = fopen(clientFilename, "w");
        if (file)
        {
            fclose(file);
            printf("Created empty client file.\n");
        }
        else
        {
            perror("Error creating client file");
            return 1; // Exit with an error code
        }
    }

    // Check if index file exists, create if not
    if (!fileExists(indexFilename))
    {
        FILE* file = fopen(indexFilename, "w");
        if (file)
        {
            fclose(file);
            printf("Created empty index file.\n");
        }
        else
        {
            perror("Error creating index file");
            return 1; // Exit with an error code
        }
    }

    while (1)
    {
        printf("\nFlight Management System\n");
        printf("1. Create Client\n");
        printf("2. Create Reservation\n");
        printf("3. Display Client\n");
        printf("4. Display Reservation\n");
        printf("5. Display All Clients\n");
        printf("6. Display All Reservations\n");
        printf("7. Modify Client\n");
        printf("8. Modify Reservation\n");
        printf("9. Delete Client\n");
        printf("10. Delete Reservation\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            {
                int code;
                char nom[100], prenom[100], adresse[100];
                printf("Enter client code: ");
                scanf("%d", &code);
                printf("Enter name: ");
                scanf("%s", nom);
                printf("Enter surname: ");
                scanf("%s", prenom);
                printf("Enter address: ");
                scanf("%s", adresse);

                Client client = createClient(code, nom, prenom, adresse);
                clientList = addClientToList(clientList, client, &indexList);
                saveClientToFile(client, clientFilename);
                saveIndex(&indexList, indexFilename);
                break;
            }
        case 2:
            {
                int code, clientCode, flightNumber, day, month, year; // Changed 'roomNumber' to 'flightNumber'
                printf("Enter reservation code: ");
                scanf("%d", &code);
                printf("Enter client code: ");
                scanf("%d", &clientCode);
                printf("Enter arrival date (day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                Date arrivalDate = createDate(day, month, year);
                printf("Enter departure date (day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                Date departureDate = createDate(day, month, year);
                printf("Enter flight number: "); // Changed 'room number' to 'flight number'
                scanf("%d", &flightNumber);

                // Here you should retrieve or create a client
                Client* client;
                // This is a placeholder, adjust as per your actual client retrieval or creation logic
                client = searchClient(clientCode, clientList, indexList);
                if (client == NULL)
                {
                    printf("Client with code %d not found.\n", clientCode);
                    // Handle the case where the client is not found
                }
                else
                {
                    Reservation reservation =
                        createReservation(code, arrivalDate, departureDate, flightNumber, *client);
                    // Changed 'roomNumber' to 'flightNumber'
                    reservationList = addReservationToList(reservationList, reservation, &indexList);
                    saveReservationToFile(reservation, reservationFilename);
                    saveIndex(&indexList, indexFilename);
                }
                break;
            }
        case 3:
            {
                int code;
                printf("Enter client code to display: ");
                scanf("%d", &code);
                // Check if clientList is not NULL before using it
                if (clientList != NULL)
                {
                    Client* foundClient = searchClient(code, clientList, indexList);

                    // Check if foundClient is not NULL before dereferencing it
                    if (foundClient != NULL && foundClient->code != -1)
                    {
                        displayClient(*foundClient);
                    }
                    else
                    {
                        printf("Client with code %d not found.\n", code);
                    }
                }
                else
                {
                    printf("Client list is empty.\n");
                }
                break;
            }
        case 4:
            {
                int code;
                printf("Enter reservation code to display: ");
                scanf("%d", &code);
                // Check if reservationList is not NULL before using it
                if (reservationList != NULL)
                {
                    Reservation* foundReservation = searchReservation(code, reservationList, indexList);

                    // Check if foundReservation is not NULL before dereferencing it
                    if (foundReservation != NULL && foundReservation->code != -1)
                    {
                        displayReservation(*foundReservation);
                    }
                    else
                    {
                        printf("Reservation with code %d not found.\n", code);
                    }
                }
                else
                {
                    printf("Reservation list is empty.\n");
                }
                break;
            }
        case 5:
            {
                displayAllClients(clientList);
            }
        case 6:
            {
                displayAllReservations(reservationList);
            }
        case 7:
            {
                int code;
                char name[100], firstName[100], address[100];
                printf("Enter client code: ");
                scanf("%d", &code);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter surname: ");
                scanf("%s", firstName);
                printf("Enter address: ");
                scanf("%s", address);
                modifyClient(&clientList, code, name, firstName, address);
                modifyClientInFile(code, name, firstName, address, clientFilename, indexFilename);
                saveIndex(&indexList, indexFilename);
                break;
            }
        case 8:
            {
                int code;
                int clientCode, flightNumber, day, month, year;
                printf("Enter reservation code: ");
                scanf("%d", &code);
                printf("Enter client code: ");
                scanf("%d", &clientCode);
                printf("Enter arrival date (day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                Date arrivalDate = createDate(day, month, year);
                printf("Enter departure date (day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                Date departureDate = createDate(day, month, year);
                printf("Enter flight number: ");
                scanf("%d", &flightNumber);
                Client* client = searchClient(clientCode, clientList, indexList);
                modifyReservation(&reservationList, code, arrivalDate, departureDate, flightNumber, *client);
                modifyReservationInFile(code, arrivalDate, departureDate, flightNumber, *client, reservationFilename,
                                        indexList);
                saveIndex(&indexList, indexFilename);
                break;
            }
        case 9:
            {
                int code;
                printf("Enter client code to delete: ");
                scanf("%d", &code);
                deleteClient(&clientList, code, &indexList);
                deleteClientFromFile(code, clientFilename, &indexList);
                saveIndex(&indexList, indexFilename);
                break;
            }
        case 10:
            {
                int code;
                printf("Enter client code to delete: ");
                scanf("%d", &code);
                deleteReservation(&reservationList, code, &indexList);
                deleteClientFromFile(code, reservationFilename, &indexList);
                saveIndex(&indexList, indexFilename);
                break;
            }

        case 11:
            printf("Exiting...\n");
        // Free allocated resources if applicable
        // freeClientList(clientList);
        // freeReservationList(reservationList);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
