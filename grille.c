#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    return (position.ordonnee * grille.largeur) + position.abscisse;
}

grille_t creer_grille(int largeur, int profondeur) {
    int nb_elem = largeur * profondeur;
    grille_t grille;
    grille.largeur = largeur;
    grille.profondeur = profondeur;
    grille.tableau = (float*)calloc(nb_elem, sizeof(float));
    return grille;
}

void detruire_grille(grille_t grille) {
    if (grille.tableau != NULL) {
        free(grille.tableau);}
    else {
        NULL;}
}

bool dans_les_bornes(grille_t grille, coord_t position) {
    return (position.abscisse <= grille.largeur - 1) && (position.ordonnee <= grille.profondeur - 1) && (position.abscisse >= 0) && (position.ordonnee >= 0);
}

int get_largeur(grille_t grille) {
    return grille.largeur;
}

int get_profondeur(grille_t grille) {
    return grille.profondeur;
}

coord_t inferieur_gauche(grille_t grille) {
    coord_t coord;
    if ((grille.largeur > 0) && (grille.profondeur > 0)) {
        coord.abscisse = 0;
        coord.ordonnee = 0;}
    else {
        NULL;}
    return coord;
}

coord_t superieur_droit(grille_t grille) {
    coord_t coord;
    if ((grille.largeur > 0) && (grille.profondeur > 0)) {
        coord.abscisse = grille.largeur - 1;
        coord.ordonnee = grille.profondeur - 1;}
    else {
        NULL;}
    return coord;
}

void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    size_t nv_hauteur = coord_lin(grille, position);
    grille.tableau[nv_hauteur] = hauteur;
}

float get_hauteur(grille_t grille, coord_t position) {
    float hauteur;
    int indice = coord_lin(grille, position);
    hauteur = grille.tableau[indice];
    return hauteur;
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    float hauteur = get_hauteur(grille, position);
    size_t nb_voisins = 0;
    coord_t voisins_valides[4];
    if (dans_les_bornes (grille, translation(position, -1, 0))){
        float diff = (get_hauteur(grille, translation(position, -1, 0)) - hauteur);
        if (diff < 0) {
            diff = (-1)*diff;}
        else {
            NULL;}
        if (diff <= seuil) {
            nb_voisins+=1;
            voisins_valides[nb_voisins - 1] = translation(position, -1, 0);}
        else {
            NULL;}    
    }
    else {
        NULL;}
    if (dans_les_bornes (grille, translation(position, 0, 1))){
        float diff = (get_hauteur(grille, translation(position, 0, 1)) - hauteur);
        if (diff < 0) {
            diff = (-1)*diff;}
        else {
            NULL;}
        if (diff <= seuil) {
            nb_voisins+=1;
            voisins_valides[nb_voisins - 1] = translation(position, 0, 1);}
        else {
            NULL;}
    }
    else {
        NULL;}
    if (dans_les_bornes (grille, translation(position, 1, 0))){
        float diff = (get_hauteur(grille, translation(position, 1, 0)) - hauteur);
        if (diff < 0) {
            diff = (-1)*diff;}
        else {
            NULL;}
        if (diff <= seuil) {
            nb_voisins+=1;
            voisins_valides[nb_voisins - 1] = translation(position, 1, 0);}
        else {
            NULL;}
    }
    else {
        NULL;}
    if (dans_les_bornes (grille, translation(position, 0, -1))){
        float diff = (get_hauteur(grille, translation(position, 0, -1)) - hauteur);
        if (diff < 0){
            diff = (-1)*diff;}
        else {
            NULL;}
        if (diff <= seuil) {
            nb_voisins+=1;
            voisins_valides[nb_voisins - 1] = translation(position, 0, -1);}
        else {
            NULL;}
    }
    else {
        NULL;}
    
    *voisins = (coord_t*)calloc(nb_voisins, sizeof(coord_t));
    if (*voisins == NULL) {
        NULL;}
    else {
        for (size_t i = 0; i < nb_voisins; i++) {
            (*voisins)[i] = voisins_valides[i];
        }
    }
    
    return nb_voisins;
}