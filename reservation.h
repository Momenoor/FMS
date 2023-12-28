#ifndef RESERVATION_H
#define RESERVATION_H

#include <stdio.h>
#include "client.h"

// Define the structure for a date
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Define the structure for a reservation
typedef struct {
    int code;
    Date arrivalDate;
    Date departureDate;
    int roomNumber;
    Client client;
} Reservation;

// Node for linked list of reservations
typedef struct ReservationList {
    Reservation reservation;
    struct ReservationList *next;
} ReservationList;

// Define the structure for the header of a file
typedef struct {
    int numberOfReservations;
    // Other metadata fields can be added here
} Header;

typedef struct {
    Reservation reservations[10];  // Array of reservations in the block
    int numReservations;           // Number of reservations currently in the block
} ReservationBlock;

// Function prototypes
Reservation createReservation(int code, Date dateA, Date dateD, int roomNumber, Client client);
Date createDate(int day, int month, int year);
ReservationList *addReservationToList(ReservationList *head, Reservation reservation);
void displayReservations(ReservationList *head);
Header readHeader(FILE *file);
void writeHeader(char *filename, Header header);
Reservation transformReservation(Reservation reservation);
ReservationBlock convertToPhysicalBlock(ReservationBlock logicalBlock);

#endif // RESERVATION_H
