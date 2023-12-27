#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>

// Create a new reservation
reservations creerReservation(int code, tdate dateA, tdate dateD,int n_chambre, clients c) {
    reservations r;
    r.codeR = code;
    r.dateA = dateA;
    r.dateD = dateD;
    r.n_chambre = n_chambre;
    r.c = c;
    return r;
}

// Add a reservation to the list
Lreservation* listeReservation(Lreservation *tete, reservations r) {
    Lreservation *nouveau = malloc(sizeof(Lreservation));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }
    nouveau->r = r;
    nouveau->next = tete;
    return nouveau;
}

// Display a reservation
void afficheR(reservations r) {
    printf("Code Reservation: %d\n", r.codeR);
    printf("Arrival Date: %d/%d/%d\n", r.dateA.jour, r.dateA.mois, r.dateA.annee);
    printf("Departure Date: %d/%d/%d\n", r.dateD.jour, r.dateD.mois, r.dateD.annee);
    printf("Room Number: %d\n", r.n_chambre);
    printf("Client Code: %d\n", r.c.code);
}

// Display the list of reservations
void afficheReservation(Lreservation *debut) {
    Lreservation *actuel = debut;
    while (actuel != NULL) {
        afficheR(actuel->r);
        actuel = actuel->next;
    }
}

// Search for a reservation by code
reservations rechercheReservation(char *nomFichier, int code) {
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    reservations r;
    while (fread(&r, sizeof(reservations), 1, file)) {
        if (r.codeR == code) {
            fclose(file);
            return r;
        }
    }

    fclose(file);

    // If the reservation is not found, return a reservation with code -1
    tdate defaultDate = {0, 0, 0}; // replace with a default date if necessary
    clients defaultClient = {0, "", "", ""}; // replace with a default client if necessary
    return creerReservation(-1, defaultDate, defaultDate, -1, defaultClient);
}

entete readTete(FILE *file) {
    entete e;
    fread(&e, sizeof(entete), 1, file);
    return e;
}

blocRPH chargerReservation(char *nomFichier, int i) {
    FILE *file = fopen(nomFichier, "rb");
    if (file == NULL) {
        printf("Unable to open file: %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    blocRPH bloc;
    fseek(file, i * sizeof(blocRPH), SEEK_SET);
    fread(&bloc, sizeof(blocRPH), 1, file);
    fclose(file);

    return bloc;
}


