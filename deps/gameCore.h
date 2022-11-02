//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

#include <allegro5/color.h>

typedef struct planeta {
    ALLEGRO_COLOR color[7];
    char *nome;
    int coordX;
    int coordY;
    int radius;
    int mass;
} Planeta;

typedef struct force {
    int Vforce; // Vertical force
    int Hforce; // Horizontal force
} Force;

Planeta* scanPlanetsYaml(int level);

void readCreatePlanets();

void moveBall();

#endif //JOGOSEMESTRE2_GAMECORE_H
