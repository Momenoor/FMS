#ifndef INDEX_H
#define INDEX_H

#include <wchar.h>
#include "struct.h"

// Function prototypes
EntreIndex creerIndex(int cle,int i,int j);
LIndex *ajoutIndex(int cle,int i,int j,LIndex *tete);
EnteteI readTeteI(FILE *file);
void writeTeteI(FILE *file,EnteteI e);
void inisialisationEntete(char* nomfichier);
void sauvegardeIndex(LIndex *liste,char *nom_fichier);
EntreIndex chargerIndex(char *nom_fichier);
LIndex *reIndexr(char *nom_fichierR,LIndex *listeI);
EntreIndex rechercheIndex(char *nom_fichier,int cle);
LIndex *insererIndex(char *nom_fichier,int cle,int i,int j,LIndex *liste);

#endif // INDEX_H