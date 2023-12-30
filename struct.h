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
// Forward declaration of the structure
typedef struct IndexList IndexList;

typedef struct {
    int i; // Can represent client ID or other identifiers
    int j; // Can represent reservation ID or other identifiers
} Address;

typedef struct {
    int key;
    Address address;
} Index;

struct IndexList {
    Index item;
    IndexList *next;
};


typedef struct {
    int num_indexes; // Number of indexes
    int updateFlag;  // Flag to indicate if the header is updated
} IndexFileHeader;
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int code;
    Date arrivalDate;
    Date departureDate;
    int flightNumber;
    Client client;
} Reservation;

typedef struct ReservationNode {
    Reservation reservation;
    struct ReservationNode *next;
} ReservationNode;




#endif // STRUCT_H