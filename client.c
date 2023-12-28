#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "struct.h"



// Function to create a new client
Client createClient(int code, char name[], char firstName[], char address[]) {
    Client c;
    c.code = code;
    strncpy(c.name, name, 49);
    c.name[49] = '\0';
    strncpy(c.firstName, firstName, 49);
    c.firstName[49] = '\0';
    strncpy(c.address, address, 99);
    c.address[99] = '\0';
    return c;
}

// Function to add a client to a linked list
ClientNode* addClientToList(ClientNode *head, Client c) {
    ClientNode *newNode = (ClientNode *)malloc(sizeof(ClientNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    newNode->client = c;
    newNode->next = head;
    return newNode;
}

// Function to display a client's information
void displayClient(Client c) {
    printf("Code: %d, Name: %s %s, Address: %s\n", c.code, c.name, c.firstName, c.address);
}

// Function to display all clients in the list
void displayAllClients(ClientNode *head) {
    ClientNode *current = head;
    while (current != NULL) {
        displayClient(current->client);
        current = current->next;
    }
}
// Function to search for a client by code in the linked list
Client* searchClient(int code, ClientNode *head) {
    ClientNode *current = head;
    while (current != NULL) {
        if (current->client.code == code) {
            return &(current->client);
        }
        current = current->next;
    }
    return NULL; // Return NULL if client not found
}

// Remember to free the allocated memory for the client list when it is no longer needed
