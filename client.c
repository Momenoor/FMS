#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "struct.h"
#include "index.h"

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
ClientNode* addClientToList(ClientNode *head, Client c, IndexList **indexList) {
    ClientNode *newNode = (ClientNode *)malloc(sizeof(ClientNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    newNode->client = c;
    newNode->next = head;

    int newPosition = 0;
    // Update the index list
    if (*indexList != NULL) {
        // Increment the index of existing clients
        IndexList *currentIdx = *indexList;
        while (currentIdx != NULL) {
            currentIdx->item.address.i += 1;
            currentIdx = currentIdx->next;
        }
    }
    *indexList = addIndex(c.code, newPosition, 0, *indexList);

    return newNode;
}


// Function to display a client's information
// Function to display a client's information
char displayClient(Client c) {
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
Client* searchClient(int code, ClientNode *head, IndexList *indexList) {
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
        return NULL; // Client not found
    }

    ClientNode *current = head;
    for (int i = 0; current != NULL && i < position; i++) {
        current = current->next;
    }

    return current != NULL ? &(current->client) : NULL;
}

void modifyClient(ClientNode **head, int code, char newName[], char newFirstName[], char newAddress[]) {
    ClientNode *current = head;

    while (current != NULL) {
        if (current->client.code == code) {
            // Modify the client's information
            strncpy(current->client.name, newName, sizeof(current->client.name) - 1);
            strncpy(current->client.firstName, newFirstName, sizeof(current->client.firstName) - 1);
            strncpy(current->client.address, newAddress, sizeof(current->client.address) - 1);
            return; // Exit the function once modified
        }
        current = current->next;
    }

    // If the client with the given code was not found
    printf("Client with code %d not found.\n", code);
}

void modifyClientInFile(int code, char newName[], char newFirstName[], char newAddress[],const char *clientFilename,const char *indexFilename) {
    long position = getClientPositionFromFile(code, indexFilename);
    if (position == -1) {
        printf("Client not found.\n");
        return;
    }

    FILE *file = fopen(clientFilename, "r+b"); // Open file for reading and writing
    if (file == NULL) {
        perror("Error opening client file");
        return;
    }

    Client client;
    fseek(file, position, SEEK_SET);
    fread(&client, sizeof(Client), 1, file);

    // Modify the client's details
    strncpy(client.name, newName, sizeof(client.name) - 1);
    strncpy(client.firstName, newFirstName, sizeof(client.firstName) - 1);
    strncpy(client.address, newAddress, sizeof(client.address) - 1);

    fseek(file, position, SEEK_SET); // Go back to the client's position
    fwrite(&client, sizeof(Client), 1, file); // Write the updated client

    fclose(file);
}

// Function to delete a client from the list and return the position of the deleted client
void deleteClientFromFile(int code, const char *clientFilename, IndexList **indexList) {
    long position = getClientPositionFromFile(code, *indexList);
    if (position == -1) {
        printf("Client not found.\n");
        return;
    }

    FILE *file = fopen(clientFilename, "r+b");
    if (file == NULL) {
        perror("Error opening client file");
        return;
    }

    Client client;
    fseek(file, position, SEEK_SET);
    fread(&client, sizeof(Client), 1, file);

    // Mark the client as deleted (assuming there's a 'deleted' flag in the Client structure)

    fseek(file, position, SEEK_SET);
    fwrite(&client, sizeof(Client), 1, file);

    fclose(file);

    // Update the index list
    deleteClientIndexByPosition(indexList, position);
}
void deleteClient(ClientNode **head, int code, IndexList **indexList) {
    ClientNode *current = *head;
    ClientNode *prev = NULL;

    while (current != NULL) {
        if (current->client.code == code) {
            // Found the client to delete
            if (prev == NULL) {
                *head = current->next; // Update the head if deleting the first node
            } else {
                prev->next = current->next; // Update the previous node's next pointer
            }
            free(current);

            // Update the index list
            return; // Client deleted, exit the function
        }
        prev = current;
        current = current->next;
    }
    printf("Client with code %d not found.\n", code);
}


void deleteClientIndexByPosition(IndexList **indexList, int position) {
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
void saveClientToFile(Client c, const char *filename) {
    FILE *file = fopen(filename, "ab"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fwrite(&c, sizeof(Client), 1, file); // Write the client to the file
    fclose(file); // Close the file
}
long getClientPositionFromFile(int clientCode, const char *indexFilename) {
    FILE *indexFile = fopen(indexFilename, "rb");
    if (indexFile == NULL) {
        perror("Error opening index file");
        return -1;
    }

    Index indexEntry;
    while (fread(&indexEntry, sizeof(Index), 1, indexFile)) {
        if (indexEntry.key == clientCode) {
            fclose(indexFile);
            return indexEntry.address.i;  // Assuming 'i' holds the file offset
        }
    }

    fclose(indexFile);
    return -1;  // Client not found
}
Client getClientFromFile(long position, const char *clientFilename) {
    FILE *clientFile = fopen(clientFilename, "rb");
    if (clientFile == NULL) {
        perror("Error opening client file");
        return (Client){0};  // Return an empty client structure
    }

    Client client;
    fseek(clientFile, position, SEEK_SET);
    fread(&client, sizeof(Client), 1, clientFile);
    fclose(clientFile);

    return client;
}



// Remember to free the allocated memory for the client list when it is no longer needed
