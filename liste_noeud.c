#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

/* TODO */

// implementation de l'enregistrement' T_Cellule
struct cellule_t {
    coord_t noeud;
    double cout;
    coord_t precedent;
    struct cellule_t* suivant;
};

liste_noeud_t* creer_liste() {
    liste_noeud_t* seed = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
    seed->noeud = (coord_t){-1,-1};
    seed->cout = INFINITY;
    seed->precedent = (coord_t){-1,-1};
    seed->suivant = NULL;
    return seed;
}

void detruire_liste(liste_noeud_t** liste_ptr) {
    if (liste_ptr == NULL) {
        return;
    }
    if (*liste_ptr == NULL) {
        return;
    }
    liste_noeud_t* courant = (*liste_ptr)->suivant;
    while (courant != NULL) {
        liste_noeud_t* a_supprimer = courant;
        courant = courant->suivant;
        free (a_supprimer);
    }
    free (*liste_ptr);
    *liste_ptr = NULL;
}

bool est_vide_liste(const liste_noeud_t* liste_ptr) {
    if (liste_ptr == NULL) {
        return false;
    }
    if (liste_ptr->suivant == NULL) {
        return true;
    }
    else {
        return false;
    }
}

bool contient_noeud_liste(const liste_noeud_t* liste_ptr, coord_t noeud) {
    if (liste_ptr == NULL) {
        return false;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL && (!memes_coord (courant->noeud, noeud))) {
        courant = courant->suivant;
    }
    if (courant == NULL) {
        return false;
    }
    else {
        return true;
    }
}

bool contient_arrete_liste (const liste_noeud_t* liste_ptr, coord_t source, coord_t destination) {
    if (liste_ptr == NULL) {
        return false;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL && !((memes_coord (courant->precedent, source)) && (memes_coord (courant->noeud, destination)))) {
        courant = courant->suivant;
    }
    if (courant == NULL) {
        return false;
    }
    else {
        return true;
    }
}

double cout_noeud_liste(const liste_noeud_t* liste_ptr, coord_t noeud) {
    double cout = INFINITY;
    if (liste_ptr == NULL) {
        return cout;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL && !(memes_coord (courant->noeud, noeud))) {
        courant = courant->suivant;
    }
    if (courant != NULL) {
        cout = courant->cout;
    }
    else {}
    return cout;
}

coord_t precedent_noeud_liste(const liste_noeud_t* liste_ptr, coord_t noeud) {
    coord_t precedent = (coord_t){-1,-1};
    if (liste_ptr == NULL) {
        return precedent;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL && !(memes_coord (courant->noeud, noeud))) {
        courant = courant->suivant;
    }
    if (courant != NULL) {
        precedent = courant->precedent;
    }
    else {}
    return precedent;
}

coord_t min_noeud_liste(const liste_noeud_t* liste_ptr) {
    double min = INFINITY;
    coord_t noeud_min = (coord_t){-1,-1};
    if (liste_ptr == NULL) {
        return noeud_min;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL) {
        if (courant->cout < min) {
            min = courant->cout;
            noeud_min = courant->noeud;
        }
        else {}
        courant = courant->suivant;
    }
    return noeud_min;
}

void inserer_noeud_liste(liste_noeud_t* liste_ptr, coord_t noeud, coord_t precedent, double cout) {
    if (liste_ptr == NULL) {
        return;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    while (courant != NULL && !(memes_coord (courant->noeud, noeud))) {
        courant = courant->suivant;
    }
    if (courant != NULL) {
        courant->precedent = precedent;
        courant->cout = cout;
    }
    else {
        courant = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
        courant->noeud = noeud;
        courant->cout = cout;
        courant->precedent = precedent;
        courant->suivant = liste_ptr->suivant;
        liste_ptr->suivant = courant;
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste_ptr, coord_t noeud) {
    if (liste_ptr == NULL) {
        return;
    }
    liste_noeud_t* courant = liste_ptr->suivant;
    liste_noeud_t* precedent = NULL;
    while (courant != NULL && !(memes_coord (courant->noeud, noeud))) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant != NULL) {
        if (precedent != NULL) {
            precedent->suivant = courant->suivant;
        }
        else {
            liste_ptr->suivant = courant->suivant;
        }
        free (courant);
    }
    else {}
}