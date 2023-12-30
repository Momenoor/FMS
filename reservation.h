#ifndef RESERVATION_H
#define RESERVATION_H

#include "index.h" // Assuming this includes the definition of IndexList
#include "client.h" // Assuming this includes the definition of IndexList

// Assuming the Date structure is defined somewhere
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

// Function prototypes
Reservation createReservation(int code, Date dateA, Date dateD, int flightNumber, Client client);
Date createDate(int day, int month, int year);
ReservationNode* addReservationToList(ReservationNode *head, Reservation c, IndexList **indexList);
void displayReservation(Reservation c);
void displayAllReservations(ReservationNode *head);
Reservation* searchReservation(int code, ReservationNode *head, IndexList *indexList);
void modifyReservationInFile(int code, Date arrivalDate, Date departureDate, int flightNumber, Client client, const char *reservationFilename, IndexList *indexList);
void deleteReservation(ReservationNode **head, int code, IndexList **indexList);
void modifyReservation(ReservationNode *head, int code, Date arrivalDate, Date departureDate, int flightNumber, Client client);
void deleteReservationFromFile(int code, const char *reservationFilename, IndexList **indexList);
void deleteReservationIndexByPosition(IndexList **indexList, int position);
void saveReservationToFile(Reservation c, const char *filename);
long getReservationPositionFromFile(int reservationCode, const char *indexFilename);
Reservation getReservationFromFile(long position, const char *reservationFilename);

#endif // RESERVATION_H
