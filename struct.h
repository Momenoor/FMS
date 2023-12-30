#ifndef STRUCT_H
#define STRUCT_H

// Define the client structure
typedef struct {
    int code;
    char name[50];
    char firstName[50];
    char address[100];
} Client;

// Define the linked list node for clients
typedef struct ClientNode {
    Client client;
    struct ClientNode *next;
} ClientNode;

typedef struct {
    char blockData[256];       // Example block data
    Client data[100]; // Array of client data
    int num;                   // Number of client data entries in this block
} ClientBlock;





#endif // STRUCT_H