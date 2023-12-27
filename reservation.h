#ifndef RESERVATION_H
#define RESERVATION_H
#include <wchar.h>
#include "struct.h"

reservations  creerReservation(int code,tdate dateA,tdate dateD,int n_chambre,clients c);
tdate creerDate(int j,int m,int a);
Lreservation * listeReservation(Lreservation *tete,reservations r);
void afficheR(reservations r);
//BlocReservation reservationToBloc(BlocReservation bloc,Lreservation *tete);
entete readTete(FILE *file);
void writeTete(char *nomFichier,entete e);
LOF *openFile(char *fichier,char mode);
reservationsPH TReservation(reservations r);
blocRPH blocphysique(BlocReservation blocR);
blocRPH chargerReservation(char *nomFichier,int i);
LIndexe *insererReservation(char *nomFichier,reservations r,LIndexe *liste);
reservations rechercheReservation(char *nomFichier,int code);
blocRPH *tabToListR(blocRPH bloc);

#endif // RESERVATION_H