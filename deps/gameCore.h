//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

#include <allegro5/color.h>

    extern struct User {
        bool active;
        int coordX;
        int coordY;
        int life;
        int radius;
    } player1 , player2;

    typedef struct {
        double coordX;
        double coordY;
        double speedX;
        double speedY;
        bool active;
    } Bullet;

    typedef struct {
        ALLEGRO_COLOR color;
        char *nome;
        int coordX;
        int coordY;
        int radius;
        double mass;
    } Planeta;

    extern Planeta planetas[2];
    extern Bullet b;
    extern float planetaSize;
    extern bool limitWalls;
    extern double NEWTON;
    extern double acel;
    extern bool gameRound;
    extern double distance;

    void initGame();

    void setBulletTo(int coordX, int coordY, int clickX, int clickY);

    void moveBall();

    void readCreatePlanetsBullets();

    double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY);

    bool hasXgap();

    bool hasYgap();

    void gameSwitch();

#endif //JOGOSEMESTRE2_GAMECORE_H
