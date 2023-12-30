#ifndef CLIENTS_H
#define CLIENTS_H
#include "struct.h"
#include "index.h"

// Function prototypes
Client createClient(int code, char name[], char firstName[], char address[]);
ClientNode *addClientToList(ClientNode *head, Client client, IndexList **indexList);
void displayAllClients(ClientNode *head);
Client* searchClient(int code, ClientNode *head, IndexList *indexList);
char displayClient(Client client);
void modifyClient(ClientNode **head, int code, char newName[], char newFirstName[], char newAddress[]);
void deleteClientIndexByPosition(IndexList **indexList, int position);
void deleteClient(ClientNode **head, int code, IndexList **indexList);
long getClientPositionFromFile(int clientCode, const char *indexFilename);
void saveClientToFile(Client c, const char *filename);
void deleteClientFromFile(int code, const char *clientFilename, IndexList **indexList);
void modifyClientInFile(int code, char newName[], char newFirstName[], char newAddress[],const char *clientFilename,const char *indexFilename);
#endif // CLIENTS_H
