#include <stdio.h>
#include "client.h"         // Contains client-related functions and structures
#include "reservation.h"    // Contains reservation-related functions and structures
#include "struct.h"         // Contains additional structure definitions

int main()
{
    int choice;
    ClientNode* clientList = NULL;
    ReservationList* reservationList = NULL;

    while (1)
    {
        printf("\nFlight Management System\n");
        printf("1. Create Client\n");
        printf("2. Create Reservation\n");
        printf("3. Display Client\n");
        printf("4. Display Reservation\n");
        printf("5. Exit\n");
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
                clientList = addClientToList(clientList, client);
                break;
            }
        case 2:
            {
                int code,clientCode , roomNumber, day, month, year;
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
                printf("Enter room number: ");
                scanf("%d", &roomNumber);

                // Here you should retrieve or create a client
                // This is a placeholder, adjust as per your actual client retrieval or creation logic
                Client client = searchClient(clientCode, clientList);

                Reservation reservation = createReservation(code, arrivalDate, departureDate, roomNumber, client);
                reservationList = addReservationToList(reservationList, reservation);
                break;
            }
        case 3:
            {
                int code;
                printf("Enter client code to display: ");
                scanf("%d", &code);
                Client foundClient = searchClient(code, clientList);
                if (foundClient.code != -1)
                {
                    displayClient(foundClient);
                }
                else
                {
                    printf("Client with code %d not found.\n", code);
                }
                break;
            }
        case 4:
            {
                int code;
                printf("Enter reservation code to display: ");
                scanf("%d", &code);
                Reservation foundReservation = searchReservation(code, reservationList);
                if (foundReservation.code != -1)
                {
                    displayReservation(foundReservation);
                }
                else
                {
                    printf("Reservation with code %d not found.\n", code);
                }
                break;
            }
        case 5:
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
