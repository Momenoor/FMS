#ifndef CLIENT_H
#define CLIENT_H
#include "struct.h"

clients creerClient(int code, char nom[], char prenom[], char adresse[]);
Lclient* listeclient(Lclient *debut, clients c);
void affiche(Lclient *debut);
clients rechercheClient(int code);
void affichec(clients c);

#endif // CLIENT_H