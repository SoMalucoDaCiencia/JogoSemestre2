//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

#include <allegro5/color.h>

    typedef struct {
        ALLEGRO_COLOR color;
        char *nome;
        int coordX;
        int coordY;
        int radius;
        int mass;
    } Planeta;

    typedef struct {
        float Vforce; // Vertical force
        float Hforce; // Horizontal force
    } Force;

    extern Planeta planetas[2];
    extern Force* allForces;
    extern int planetaSize;
    extern int ballRadius;
    extern int ballSpeedX;
    extern int ballSpeedY;
    extern int ballXCoord;
    extern int ballYCoord;
    extern double NEWTON;
    extern double acel;

    void initGame();

    void moveBall();

    Planeta* scanPlanetsYaml(int level);

    void readCreatePlanets();

    double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY);

#endif //JOGOSEMESTRE2_GAMECORE_H
