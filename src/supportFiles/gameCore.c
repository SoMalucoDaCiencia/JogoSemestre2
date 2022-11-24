//
// Created by Arthur Andrade - home on 12/10/22.
//

#include <stdio.h>
#include "gameCore.h"
#include "nossaLivraria.h"
#include <Cores.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <src/main.h>

Planeta planetas[2];
 Bullet* bullets;
Force* allForces;

float planetaSize;
float ballRadius;
float ballSpeedX;
float ballSpeedY;
float ballXCoord;
float ballYCoord;
bool limitWalls;
double NEWTON;
double acel;

void initGame() {

    planetas[0].color = RED;
    planetas[0].nome = "Arthur";
    planetas[0].coordX = WINDOW_WIDTH/2 - 30;
    planetas[0].coordY = WINDOW_HEIGHT/2;
    planetas[0].radius = 20;
    planetas[0].mass = 1;

//    planetas[1].color = DARK_BLUE;
//    planetas[1].nome = "Tais";
//    planetas[1].coordX = 200;
//    planetas[1].coordY = 590;
//    planetas[1].radius = 30;
//    planetas[1].mass = 2;

    planetaSize = sizeof(planetas) / sizeof(Planeta);

//    NEWTON = 6.6743 * pow(10, -11);
    NEWTON = 6.6743 * pow(10, 0);
    limitWalls = false;

//    gamePaused = false;
    ballRadius = 01;
    ballSpeedX = 1;
    ballSpeedY = 1;
    ballXCoord = 750;
    ballYCoord = 155;
}

void moveBall() {
    allForces = malloc(planetaSize * sizeof(Force));
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];

        acel = NEWTON * planeta.mass / twoPointsDistance(ballXCoord, ballYCoord, planeta.coordX, planeta.coordY);
        Force force;
        force.Hforce = 0;
        if (planeta.coordY >= ballYCoord) {
            force.Vforce = acel;
        } else if (planeta.coordY < ballYCoord) {
            force.Vforce = acel * (-1);
        }
        allForces[i] = force;

        Force force2;
        force2.Vforce = 0;
        if (planeta.coordX >= ballXCoord) {
            force2.Hforce = acel;
        } else if (planeta.coordX < ballXCoord) {
            force2.Hforce = acel * (-1);
        }
        allForces[i] = force2;

        if (twoPointsDistance(ballXCoord, ballYCoord, planeta.coordX, planeta.coordY)<=ballRadius+(planeta.radius)) {
            ballYCoord = floor(getRandomInt(WINDOW_HEIGHT, 0) * WINDOW_HEIGHT);
            ballXCoord = floor(getRandomInt(WINDOW_WIDTH, 0) * WINDOW_WIDTH);
            ballSpeedY = 3;
            ballSpeedX = 3;
        }
        if (twoPointsDistance(ballXCoord, ballYCoord, planeta.coordX, planeta.coordY) <= ballRadius + planeta.radius) {
            ballYCoord = floor(getRandomInt(WINDOW_HEIGHT, 0) * WINDOW_HEIGHT);
            ballXCoord = floor(getRandomInt(WINDOW_WIDTH, 0) * WINDOW_WIDTH);
            ballSpeedY = 5;
            ballSpeedX = 5;
        }
    }

    float finalXAceleration = 0;
    float finalYAceleration = 0;
    for (int i = 0; i < planetaSize; ++i) {
        Force force = allForces[i];
        finalYAceleration += (force.Vforce);
        finalXAceleration += (force.Hforce);
    }
    free(allForces);
    ballSpeedY += finalYAceleration / 3;
    ballSpeedX += finalXAceleration / 3;

    if (limitWalls) {
        if (hasYgap()) {
            ballSpeedY *= -1;
        }
        if (hasXgap()) {
            ballSpeedX *= -1;
        }
    }

    ballYCoord += ballSpeedY;
    ballXCoord += ballSpeedX;
} //acaba o moveball

Planeta* scanPlanetsYaml(int level) {

}

void readCreatePlanets(){
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        al_draw_filled_circle((float) planeta.coordX, (float)  planeta.coordY, (float)  planeta.radius, planeta.color);
    }
}

double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY) {
    const int x = (pointAX > pointBX ? (pointAX - pointBX) : (pointBX - pointAX));
    const int y = (pointAY > pointBY ? (pointAY - pointBY) : (pointBY - pointAY));

    return floor(sqrt(pow(x, 2) + pow(y, 2)));
}

// Verifica se a bolinha vai bater na esquerda ou na direita
bool hasXgap() {
    if (ballSpeedX>0) {
        return (round(ballXCoord + ballSpeedX + ballRadius) >= WINDOW_WIDTH);
    } else {
        return (floor(ballXCoord - ballSpeedX - ballRadius) <= 0);
    }
}

// Verifica se a bolinha vai bater no teto ou no chao
bool hasYgap() {
    if (ballSpeedY>0) {
        return (round(ballYCoord + ballSpeedY + ballRadius) >= WINDOW_HEIGHT);
    } else {
        return (floor(ballYCoord - ballSpeedY - ballRadius) <= 0);
    }
}