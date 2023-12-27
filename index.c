//............................................................................//
#include "struct.h"
#include "index.h"
#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>

//creation de l'Index

EntreIndex creerIndex(int cle, int i, int j) {
    EntreIndex in;
    in.cle = cle;
    in.adrs.i = i;
    in.adrs.j = j;
    return in;
}

//creation de la liste chainee pour les Indexs
LIndex *ajoutIndex(int cle, int i, int j, LIndex *tete) {
    LIndex *element = (LIndex *) malloc(sizeof(LIndex));
    EntreIndex in = creerIndex(cle, i, j);
    element->elem = in;
    element->next = NULL;
    if (tete == NULL || in.cle < tete->elem.cle) {
        //verifi si la liste est vide ou la cle est plus petite que la cle qui se trouve dans la tete de la liste
        element->next = tete;
        tete = element;
        return tete;
    } else {
        LIndex *tmp = tete;
        while (tmp->next != NULL && (tmp->next->elem.cle) < in.cle) {
            tmp = tmp->next; //element suivant pour le parcour de la liste et pour  et trouve l'emplacement de l'element
        }
        element->next = tmp->next;
        tmp->next = element;
        return tete;
    }
}

//pour le fichier d'Indexs
EnteteI readTeteI(FILE *file) {
    EnteteI e;
    rewind(file); //mettre le curseur au debut
    fread(&(e), sizeof(EnteteI), 1, file); //lire l'entete
    rewind(file); //remettre le cusrseur au debut
    return e;
}

//ecrire l'entete
void writeTeteI(FILE *file, EnteteI e) {
    rewind(file); //mettre le curseur au debut
    fwrite(&(e), sizeof(EnteteI), 1, file); //ecrire l'entete
    //rewind(file);//remettre le cusrseur au debut
}

void inisialisationEntete(char *nomfichier) {
    EnteteI e;
    FILE *f = fopen(nomfichier, "wb"); // Ouvrir le fichier en mode écriture binaire
    e.nbr_Indexs = 0;
    writeTeteI(f, e);
    rewind(f);
    fclose(f); // Fermeture du fichier
}

//sauvegarde les Indexs dans le fichier d'Index
void sauvegardeIndex(LIndex *liste, char *nom_fichier) {
    LIndex *tete = liste;
    EnteteI e;
    e.nbr_Indexs = 0;
    while (tete != NULL) {
        e.nbr_Indexs++;
        tete = tete->next;
    }
    // printf("\n%d",e.nbr_Indexs);
    e.maj = 1;
    tete = liste;
    FILE *file = fopen(nom_fichier, "wb+");
    writeTeteI(file, e);
    fwrite(&(e), sizeof(EnteteI), 1, file);
    while (tete != NULL) {
        fwrite(&(tete->elem), sizeof(EntreIndex), 1, file);
        tete = tete->next;
    }
    fclose(file);
}

//charger un Index
EntreIndex chargerIndex(char *nom_fichier) {
    EntreIndex in;
    FILE *f = fopen(nom_fichier, "rb");
    fseek(f, sizeof(EnteteI),SEEK_SET);
    fread(&(in), sizeof(EntreIndex), 1, f);
    fclose(f);
    printf("%d  %d  %d", in.cle, in.adrs.i, in.adrs.j);
    return in;
}


//recherche par cle dans les Indexs
EntreIndex rechercheIndex(char *nom_fichier, int cle) {
    EntreIndex in;
    FILE *f = fopen(nom_fichier, "rb");
    EnteteI e = readTeteI(f);
    int i = 0;
    for (i = 0; i < e.nbr_Indexs; i++) {
        fread(&(in), sizeof(EntreIndex), 1, f);
        if (in.cle == cle) {
            fclose(f);
            return in;
        }
    }
    fclose(f);
    printf("l'element n'existe pas");
    return in;
}

//fonction reIndexr
LIndex *reIndexr(char *nom_fichierR, LIndex *listeI) {
    LIndex *tete;
    FILE *f = fopen(nom_fichierR, "rb");
    entete e = readTete(f); //lire l'entete
    for (int i = 1; i <= e.nbr_bloc; i++) {
        blocRPH bloc = chargerReservation(nom_fichierR, i); //charger les bloc un par un
        for (int j = 0; j < bloc.nbr_enregistrement; j++) {
            listeI = ajoutIndex(bloc.donne[j].codeR, i, j, listeI); //creation des Indexs
        }
    }
    fclose(f);
    return listeI;
}
