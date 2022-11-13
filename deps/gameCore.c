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
#include <allegro5/allegro_font.h>

Planeta planetas[2];
Bullet b;

struct User player1 , player2;

float planetaSize;
bool limitWalls;
bool gameRound = true; //True == player1 and False == player2
double NEWTON;
double acel;

void initGame() {

    b.speedX = 0;
    b.speedY = 0;

    planetas[0].color = RED;
    planetas[0].nome = "Arthur";
    planetas[0].coordX = WINDOW_WIDTH/2;
    planetas[0].coordY = WINDOW_HEIGHT/2;
    planetas[0].radius = 20;
    planetas[0].mass = 0;

    player1.coordY =  WINDOW_HEIGHT/4 - planetas[0].radius;
    player1.coordX =  WINDOW_WIDTH/2;

    player2.coordY =  WINDOW_HEIGHT/4 - planetas[0].radius;
    player2.coordX =  WINDOW_WIDTH/5;

    planetas[1].color = WHITE;
    planetas[1].nome = "Tais";
    planetas[1].coordX = 200;
    planetas[1].coordY = 590;
    planetas[1].radius = 30;
    planetas[1].mass = 0;

    planetaSize = sizeof(planetas) / sizeof(Planeta);

    b.coordX = planetas[0].coordX;
    b.coordY = planetas[0].coordY - planetas[0].radius;

//    NEWTON = 6.6743 * pow(10, -11);
    NEWTON = 6.6743 * pow(10, 0);
    limitWalls = false;
}

void moveBall() {

    double finalXAceleration = 0;
    double finalYAceleration = 0;

    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];

        if(planeta.nome != NULL){
            double distance = twoPointsDistance(planeta.coordX, planeta.coordY, b.coordX, b.coordY);
            if (1.0 + planeta.radius >= distance) {
                b.active = false;
                gameRound = !gameRound; //Inverte a rodada
            }

            acel = NEWTON * planeta.mass / twoPointsDistance(b.coordX, b.coordY, planeta.coordX, planeta.coordY);

            finalYAceleration += getComposedCoefficient(acel, b.coordX, b.coordY, planeta.coordX, planeta.coordY);
            if (planeta.coordY <= b.coordY && b.coordY < 0) {
                finalYAceleration *= -1;
            }

            double forceX = (double) sqrt(acel * acel - finalYAceleration * finalYAceleration);
            if (planeta.coordX <= b.coordX) {
                forceX *= -1;
            }
            finalXAceleration += forceX;
        }
    }

    if(hasXgap() || hasYgap()){
        b.active = false;
        gameRound = !gameRound; //Inverte a rodada
    }

    (b).speedY += finalYAceleration;
    (b).speedX += finalXAceleration;

    (b).coordY += b.speedY;
    (b).coordX += b.speedX;

} //acaba o moveball

Planeta* scanPlanetsYaml(int level) {

}

void gameSwitch(){
    gameRound = !gameRound;
    player1.active = !player1.active;
    player2.active = !player2.active;
}

void readCreatePlanetsBullets(){
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        al_draw_filled_circle((float) planeta.coordX, (float)  planeta.coordY, (float)  planeta.radius, planeta.color);
    }
    if(b.active) {
    al_draw_filled_circle((float) b.coordX, (float)  b.coordY, 1, WHITE);
    }else {
        al_draw_filled_circle((float)WINDOW_WIDTH * 2, (float) WINDOW_HEIGHT * 2, 1, WHITE);
        b.speedX = 0;
        b.speedY = 0;
    }
}

double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY) {
    const int x = (pointAX > pointBX ? (pointAX - pointBX) : (pointBX - pointAX));
    const int y = (pointAY > pointBY ? (pointAY - pointBY) : (pointBY - pointAY));

    return floor(sqrt(pow(x, 2) + pow(y, 2)));
}

void setBulletTo(int coordX, int coordY, int clickX, int clickY) {
    b.active = true;
    int velInit = 10; // Velocidade inicial
    if(gameRound){
        b.speedY = getComposedCoefficient(velInit, player1.coordX, player1.coordY, clickX, clickY);
        b.coordY = player1.coordY;
        b.coordX = player1.coordX;
    }else{
        b.speedY = getComposedCoefficient(velInit, player2.coordX, player2.coordY, clickX, clickY);
        b.coordY = player2.coordY;
        b.coordX = player2.coordX;
    }
    if (clickY<=coordY) {
        b.speedY *= -1;
    }

    b.speedX = (double) sqrt(velInit*velInit - b.speedY*b.speedY);
    if (clickX <= coordX) {
        b.speedX *= -1;
    }


}

// Verifica se a bolinha vai bater na esquerda ou na direita
bool hasXgap() {
    if (b.speedX>0) {
        return (round(b.coordX + b.speedX + 1.0) >= WINDOW_WIDTH);
    } else {
        return (floor(b.coordX - b.speedX - 1.0) <= 0);
    }
}

// Verifica se a bolinha vai bater no teto ou no chao
bool hasYgap() {
    if (b.speedY>0) {
        return (round(b.coordY + b.speedY + 1.0) >= WINDOW_HEIGHT);
    } else {
        return (floor(b.coordY - b.speedY - 1.0) <= 0);
    }
}



