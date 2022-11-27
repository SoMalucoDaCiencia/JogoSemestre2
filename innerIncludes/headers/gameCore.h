//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_GAMECORE_H
#define JOGOSEMESTRE2_GAMECORE_H

#include <allegro5/color.h>
#include <innerIncludes/headers/Interpreter.h>
#include <innerIncludes/headers/sprites.h>


    extern struct User {
        SPRITE character;
        int coordX;
        int coordY;
        int radius;
        int life;
    } player1 , player2;

    typedef struct {
        double coordX;
        double coordY;
        double speedX;
        double speedY;
        bool active;
        float radius;
    } Bullet;

    typedef struct {
        ALLEGRO_COLOR color;
        char *nome;
        int coordX;
        int coordY;
        int radius;
        double mass;
    } Planeta;

    extern Planeta *planetas;
    extern Bullet b;
    extern float planetaSize;
    extern bool limitWalls;
    extern double NEWTON;
    extern double acel;
    extern bool gameRound;
    extern double distance;

    extern MAP activeMap;

    void initGame();

    void finishGame();

    void setBulletTo(int clickX, int clickY);

    void moveBall();

    void readCreatePlanetsBullets();

    double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY);

    bool hasXgap();

    bool hasYgap();

#endif //JOGOSEMESTRE2_GAMECORE_H
