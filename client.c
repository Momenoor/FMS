#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new client
clients creerClient(int code, char nom[], char prenom[], char adresse[]) {
    clients c;
    c.code = code;
    strncpy(c.nom, nom, sizeof(c.nom));
    strncpy(c.prenom, prenom, sizeof(c.prenom));
    strncpy(c.adresse, adresse, sizeof(c.adresse));

    FILE *file = fopen("clients.txt", "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return c;
    }

    fprintf(file, "%d, %s, %s, %s\n", c.code, c.nom, c.prenom, c.adresse); // Write client data to file
    fclose(file); // Close the file

    return c;
}


// Add a client to the list
Lclient* listeclient(Lclient *debut,clients c) {
    Lclient *nouveau = malloc(sizeof(Lclient));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }
    nouveau->c = c;
    nouveau->next = debut;
    return nouveau;
}

// Display a client
void affichec(clients c) {
    if (c.code == -1) {
        printf("Client not found or error occurred.\n");
    } else {
        printf("Code: %d\n", c.code);
        printf("Nom: %s\n", c.nom);
        printf("Prenom: %s\n", c.prenom);
        printf("Adresse: %s\n", c.adresse);
    }
}


// Display the list of clients
void affiche(Lclient *debut) {
    Lclient *actuel = debut;
    while (actuel != NULL) {
        affichec(actuel->c);
        actuel = actuel->next;
    }
}

// Search for a client by code
clients rechercheClient(int code) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return (clients){-1, "", "", ""}; // Return a default client indicating error
    }

    clients c;
    while (fscanf(file, "%d, %99[^,], %99[^,], %99[^\n]\n", &c.code, c.nom, c.prenom, c.adresse) == 4) {
        if (c.code == code) {
            fclose(file);
            return c; // Return the found client
        }
    }

    fclose(file);
    return (clients){-1, "", "", ""}; // Client not found
}

tdate creerDate(int j, int m, int a) {
    tdate newDate;
    newDate.jour = j;
    newDate.mois = m;
    newDate.annee = a;
    return newDate;
}
