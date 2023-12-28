#ifndef CLIENTS_H
#define CLIENTS_H
#include "struct.h"

// Function prototypes
Client createClient(int code, char name[], char firstName[], char address[]);
ClientNode *addClientToList(ClientNode *head, Client client);
void displayAllClients(ClientNode *head);
Client* searchClient(int code, ClientNode *head);
void displayClient(Client client);

#endif // CLIENTS_H
