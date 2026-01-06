#include "coord.h"
//%cflags: -I .
//%ldflags: -L. -lt
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
// TODO : implanter le module coord

coord_t creer_coord (int abs, int ord) {
    coord_t coord;
    coord.abscisse = abs;
    coord.ordonnee = ord;
    return coord;
}

int get_x (coord_t coord) {
    return coord.abscisse;
}

int get_y (coord_t coord) {
    return coord.ordonnee;
}

void set_x (coord_t *coord, int x) {
    coord->abscisse = x;
}

void set_y (coord_t *coord, int y) {
    coord->ordonnee = y;
}

bool memes_coord (coord_t coord1, coord_t coord2) {
    return (coord1.abscisse == coord2.abscisse) && (coord1.ordonnee == coord2.ordonnee);
        }

coord_t translation (coord_t coord, int dx, int dy) {
    coord.abscisse += dx;
    coord.ordonnee += dy;
    return coord;
}

float distance_euclidienne (coord_t coord1, coord_t coord2) {
    float dist;
    dist = ((coord2.abscisse - coord1.abscisse)*(coord2.abscisse - coord1.abscisse)) + ((coord2.ordonnee - coord1.ordonnee)*(coord2.ordonnee - coord1.ordonnee));
    dist = sqrt(dist);
    return dist;
}