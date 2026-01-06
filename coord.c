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
    coord.x = abs;
    coord.y = ord;
    return coord;
}

int get_x (coord_t coord) {
    return coord.x;
}

int get_y (coord_t coord) {
    return coord.y;
}

void set_x (coord_t *coord, int x) {
    coord->x = x;
}

void set_y (coord_t *coord, int y) {
    coord->y = y;
}

bool memes_coord (coord_t coord1, coord_t coord2) {
    return (coord1.x == coord2.x) && (coord1.y == coord2.y);
        }

coord_t translation (coord_t coord, int dx, int dy) {
    coord.x += dx;
    coord.y += dy;
    return coord;
}

float distance_euclidienne (coord_t coord1, coord_t coord2) {
    float dist;
    dist = ((coord2.x - coord1.x)*(coord2.x - coord1.x)) + ((coord2.y - coord1.y)*(coord2.y - coord1.y));
    dist = sqrt(dist);
    return dist;
}