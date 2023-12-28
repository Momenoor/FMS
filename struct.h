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
    int block;      // Block number
    int position;   // Position within the block
} Address;

#define MAX_ADDRESSES 100  // Define a maximum number of addresses

typedef struct {
    int id;                     // Unique identifier for the index
    char name[50];              // Name associated with the index
    Address addresses[MAX_ADDRESSES]; // Array of addresses
    int numAddresses;           // Number of addresses in the array
} Index;

typedef struct IndexNode {
    Index index;             // The index data
    struct IndexNode *next;  // Pointer to the next node
} IndexNode;

typedef struct IndexList {
    Index index;          // The index data
    struct IndexList *next;   // Pointer to the next node in the list
} IndexList;

typedef struct {
    int numIndices;       // Number of indices
    int isUpdated;        // Flag indicating whether the index is updated
    // Other metadata fields can be added here
} IndexHeader;

typedef struct {
    char blockData[256];       // Example block data
    Client data[100]; // Array of client data
    int num;                   // Number of client data entries in this block
} ClientBlock;





#endif // STRUCT_H