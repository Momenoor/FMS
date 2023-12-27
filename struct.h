#ifndef STRUCT_H
#define STRUCT_H

#define MAX_KEYS 3
#include <wchar.h>
#include "struct.h"


typedef struct {
    int nbr_Indexs; // Number of nodes
    int maj; // 1 if the index is updated, 0 otherwise
} EnteteI;

typedef struct {
    int i; // The block number
    int j; // The index of the reservation in the block
} adrs;

typedef struct {
    int cle;
    int i;
    int j;
    adrs adrs;
} EntreIndex;

typedef struct LIndexe {
    EntreIndex elem; // The element of the node
    struct LIndexe *next; // Pointer to the next node
} LIndexe;


typedef struct {
    int code;
    char nom[100];
    char prenom[100];
    char adresse[100];
} clients;

typedef struct Lclient {
    clients c;
    struct Lclient *next;
} Lclient;

typedef struct LIndex {
    EntreIndex elem;
    struct LIndex *next;
} LIndex;


typedef struct {
    int nbr_bloc;
    int maj;
} entete;

typedef struct {
    int jour;
    int mois;
    int annee;
} tdate;

typedef struct {
    int codeR;
    tdate dateA;
    tdate dateD;
    int n_chambre;
    clients c;
} reservations;

typedef struct Lreservation {
    reservations r;
    struct Lreservation *next;
} Lreservation;

typedef struct {
    int nbr_enregistrement;
    reservations donne[100];
} BlocReservation;

typedef struct {
    int mode;
    FILE *f;
} LOF;

typedef struct {
    int codeR;
    int codeC;
    int codeV;
    int jour;
    int mois;
    int annee;
} reservationsPH;

typedef struct {
    int nbr_enregistrement;
    reservationsPH donne[100];
} blocRPH;

#endif // STRUCT_H