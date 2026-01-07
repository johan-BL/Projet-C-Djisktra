#ifndef COORD_H
#define COORD_H
#include <stdbool.h>
#include <stdio.h>

struct coord_t {
    int x;
    int y;
};

typedef struct coord_t coord_t;

coord_t creer_coord (int abs, int ord);

int get_x (coord_t coord);
int get_y (coord_t coord);

void set_x (coord_t *coord, int x);
void set_y (coord_t *coord, int y);

bool memes_coord (coord_t coord1, coord_t coord2);

coord_t translation (coord_t coord, int dx, int dy);

float distance_euclidienne (coord_t coord1, coord_t coord2);

#endif // COORD_H