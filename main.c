#include <stdio.h>
#include "client.h"
#include "reservation.h"
#include "struct.h"

int main() {
    int choice;
    while (1) {
        printf("Flight Management System\n");
        printf("1. Create Client\n");
        printf("2. Create Reservation\n");
        printf("3. Display Client\n");
        printf("4. Display Reservation\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
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

                clients client = creerClient(code, nom, prenom, adresse);
                // Add client to the client list (if you have a client list structure)
                break;
            }
            case 2: {
                int code, n_chambre, j, m, a;
                printf("Enter reservation code: ");
                scanf("%d", &code);
                printf("Enter arrival date (day month year): ");
                scanf("%d %d %d", &j, &m, &a);
                const tdate dateA = creerDate(j, m, a);
                printf("Enter departure date (day month year): ");
                scanf("%d %d %d", &j, &m, &a);
                const tdate dateD = creerDate(j, m, a);
                printf("Enter room number: ");
                scanf("%d", &n_chambre);

                // Assuming a client is already created and stored in client variable
                // You might need to adjust this part based on how you're storing and retrieving clients
                const clients client;
                reservations reservation = creerReservation(code, dateA, dateD, n_chambre, client);
                // Add reservation to the reservation list (if you have such a structure)
                break;
            }
            case 3: {
                int code;
                printf("Enter client code to display: ");
                scanf("%d", &code);


                const clients foundClient = rechercheClient(code);

                if (foundClient.code != -1) {
                    affichec(foundClient);
                } else {
                    printf("Client with code %d not found.\n", code);
                }
                break;
            }
            case 4: {
                int code;
                printf("Enter reservation code to display: ");
                scanf("%d", &code);

                // Assuming you have a list of reservations (Lreservation *reservationList)
                // You need to have already created this list in your program
                Lreservation *reservationList = NULL; // This should be initialized with your reservation list
                const reservations foundReservation = rechercheReservation(code, reservationList);

                if (foundReservation.codeR != -1) {
                    afficheR(foundReservation);
                } else {
                    printf("Reservation with code %d not found.\n", code);
                }
                break;
            }
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
