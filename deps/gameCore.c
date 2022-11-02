//
// Created by Arthur Andrade - home on 12/10/22.
//

#include <stdbool.h>
#include <stdio.h>
#include "gameCore.h"
#include "nossaLivraria.h"
#include <Cores.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <src/main.h>

double NEWTON;
Force* allForces;
bool gamePaused;
int ballRadius;
int ballSpeedX;
int ballSpeedY;
int ballXCoord;
int ballYCoord;

double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY) {
    const int x = (pointAX > pointBX ? (pointAX - pointBX) : (pointBX - pointAX));
    const int y = (pointAY > pointBY ? (pointAY - pointBY) : (pointBY - pointAY));

    return floor(sqrt(pow(x, 2) + pow(y, 2)));

}

int planetaSize;
Planeta planetas[2];

void initGame(){

    planetas[0].nome = "Arthur";
    planetas[0].coordX = 10;
    planetas[0].coordY = 10;
    planetas[0].radius = 10;
    planetas[0].mass = 10;

    planetas[1].nome = "Tais";
    planetas[1].coordX = 20;
    planetas[1].coordY = 20;
    planetas[1].radius = 20;
    planetas[1].mass = 20;

    //Fazer malloc
    // AllForces = malloc alguma coisa (linha 74)

    planetaSize = sizeof(planetas)/sizeof(Planeta);


    allForces = malloc (planetaSize * sizeof (int));
    for (int i = 0; i < planetaSize; ++i){
        Force force = allForces[i];
    }


      NEWTON = 6.6743 * pow(10, -11);
      gamePaused = false;
      ballRadius = 1;
      ballSpeedX = -2;
      ballSpeedY = 0;
      ballXCoord = 950;
      ballYCoord = 55;
}

void moveBall() {
        allForces = malloc (planetaSize * sizeof (int));
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

        force.Vforce = 0;
        if (planeta.coordX >= ballXCoord) {
            force.Hforce = acel;
        } else if (planeta.coordX < ballXCoord) {
            force.Hforce = acel * (-1);
        }

        if (twoPointsDistance(ballXCoord, ballYCoord, planeta.coordX, planeta.coordY) <=
            ballRadius + planeta.radius) {
            ballYCoord = floor(getRandomInt(WINDOW_HEIGHT , 0) * WINDOW_HEIGHT);
            ballXCoord = floor(getRandomInt(WINDOW_WIDTH , 0) * WINDOW_WIDTH);
            ballSpeedY = 3;
            ballSpeedX = 3;
        }
        if (twoPointsDistance(ballXCoord, ballYCoord, planeta.coordX, planeta.coordY)<=ballRadius+planeta.radius) {
            ballYCoord = floor(getRandomInt(WINDOW_HEIGHT , 0) * WINDOW_HEIGHT);
            ballXCoord = floor(getRandomInt(WINDOW_WIDTH , 0) * WINDOW_WIDTH);
            ballSpeedY = 5;
            ballSpeedX = 5;
        }
    }

    float finalXAceleration = 0;
    float finalYAceleration = 0;
    for(int i = 0; i < planetaSize; ++i){
        Force force = allForces[i];
        finalYAceleration += (force.Vforce);
        finalXAceleration += (force.Hforce);
    }
    ballSpeedY += finalYAceleration/300;
    ballSpeedX += finalXAceleration/300;

    ballYCoord += ballSpeedY;
    ballXCoord += ballSpeedX;
} //acaba o moveball


Planeta* scanPlanetsYaml(int level) {

}

void readCreatePlanets(){
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        al_draw_filled_circle(planeta.coordX, planeta.coordY, planeta.radius, planeta.color);
    }
}


//}