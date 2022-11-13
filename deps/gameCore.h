//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

#include <allegro5/color.h>

    typedef struct {
        unsigned short ID;
        int coordX;
        int coordY;
    } User;

    typedef struct {
        double coordX;
        double coordY;
        double speedX;
        double speedY;
    } Bullet;

    typedef struct {
        ALLEGRO_COLOR color;
        char *nome;
        int coordX;
        int coordY;
        int radius;
        double mass;
    } Planeta;

    extern Planeta planetas[1];
    extern Bullet b;
    extern float planetaSize;
    extern bool limitWalls;
    extern double NEWTON;
    extern double acel;

    void initGame();

    void setBulletTo(int coordX, int coordY, int clickX, int clickY);

    void moveBall();

    Planeta* scanPlanetsYaml(int level);

    void readCreatePlanetsBullets();

    double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY);

    bool hasXgap();

    bool hasYgap();

#endif //JOGOSEMESTRE2_GAMECORE_H
