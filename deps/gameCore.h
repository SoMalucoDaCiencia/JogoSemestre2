//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

float acel;
int ballRadius;
int ballSpeedX;
int ballSpeedY;
int ballXCoord;
int ballYCoord;

#include <allegro5/color.h>

typedef struct planeta {
    ALLEGRO_COLOR color;
    char *nome;
    int coordX;
    int coordY;
    int radius;
    int mass;
} Planeta;

typedef struct force {
    float Vforce; // Vertical force
    float Hforce; // Horizontal force
} Force;

Planeta* scanPlanetsYaml(int level);

void readCreatePlanets();

void moveBall();

#endif //JOGOSEMESTRE2_GAMECORE_H
