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
        unsigned short ID;
        double coordX;
        double coordY;
        double speedX;
        double speedY;
        float Vforce; // Vertical force
        float Hforce; // Horizontal force
    } Bullet;

    typedef struct {
        ALLEGRO_COLOR color;
        char *nome;
        int coordX;
        int coordY;
        int radius;
        int mass;
    } Planeta;

    extern Planeta planetas[2];
    extern Bullet* bullets;
    extern float planetaSize;
    extern float ballRadius;
    extern float ballSpeedX;
    extern float ballSpeedY;
    extern float ballXCoord;
    extern float ballYCoord;
    extern bool limitWalls;
    extern double NEWTON;
    extern double acel;

    void initGame();

    Bullet initBullet(int coordX, int coordY, int clickX, int clickY, int id);

    void insertBullet(int clickX, int clickY);

    void moveBall();

    Planeta* scanPlanetsYaml(int level);

    void readCreatePlanetsBullets();

    double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY);

    bool hasXgap();

    bool hasYgap();

#endif //JOGOSEMESTRE2_GAMECORE_H
