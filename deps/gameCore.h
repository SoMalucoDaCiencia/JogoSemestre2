//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

typedef struct planeta {
    char nome[30];
    int coordx;
    int coordY;
    int radius;
    int mass;
    char color[7];
} Planeta;

Planeta* scanPlanetsYaml(int level);

void readCreatePlanets();

void moveBall();

#endif //JOGOSEMESTRE2_GAMECORE_H
