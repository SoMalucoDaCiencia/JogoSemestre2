//
// Created by Arthur Andrade - home on 12/10/22.
//

#include <stdio.h>
#include <innerIncludes/headers/gameCore.h>
#include <innerIncludes/headers/nossaLivraria.h>
#include <innerIncludes/headers/Cores.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <src/main.h>
#include <allegro5/allegro_font.h>

Planeta *planetas;
MAP activeMap;
Bullet b;

struct User player1 , player2;

float planetaSize;
bool limitWalls;
bool gameRound; //True == player1 and False == player2
double NEWTON;
double acel;

void initGame() {

    b.speedX = 0;
    b.speedY = 0;

    readSetPlanet();
//    planetas[0].color = WHITE;
//    planetas[0].nome = "Arthur";
//    planetas[0].coordX = WINDOW_WIDTH/2;
//    planetas[0].coordY = WINDOW_HEIGHT/2;
//    planetas[0].radius = 20;
//    planetas[0].mass = 0.3;
//
//    planetas[1].color  = WHITE;
//    planetas[1].nome   = "Tais";
//    planetas[1].coordX = 200;
//    planetas[1].coordY = 560;
//    planetas[1].radius = 30;
//    planetas[1].mass   = 0.3;

    if(getRandomInt(1, 0) == 0) {
        player1.active = true;
        player2.active = false;
        gameRound = true;
    } else {
        player1.active = false;
        player2.active = true;
        gameRound = false;
    }

    player1.coordY =  planetas[0].coordY - ((planetas[0].radius + player1.radius) * 2);
    player1.coordX =  planetas[0].coordX;
    player1.life   = 5;
    player1.radius = 12;

    player2.coordY =  planetas[1].coordY - ((planetas[1].radius + player2.radius) * 1.5);
    player2.coordX =  planetas[1].coordX;
    player2.life   = 5;
    player2.radius = 12;

    if (gameRound) {
        b.coordY = player1.coordY;
        b.coordX = player1.coordX;
    } else {
        b.coordY = player2.coordY;
        b.coordX = player2.coordX;
    }

//    NEWTON = 6.6743 * pow(10, -11);
    NEWTON = 6.6743 * innerPow(10, 1);
    limitWalls = false;
}

void finishGame(){
    int SAVEGAMEMODE = (int) GAMESTATE;
    GAMESTATE = TRANSITION;
    waitTime((float) 2.5);
    initGame();
    activeMap++;
    GAMESTATE = (GAMEMODE) SAVEGAMEMODE;
}

void moveBall() {

    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        double finalXAceleration = 0;
        double finalYAceleration = 0;

        if(planeta.nome != NULL){
            bool inverter = false;
            //hitbox planeta
            double distance = twoPointsDistance(planeta.coordX, planeta.coordY, b.coordX, b.coordY);
            if ((5.0 + planeta.radius >= distance) && b.active) {
                b.active = false;
                inverter = true;
            }

            //hitbox player1
              double distancePlayer1 = twoPointsDistance(player1.coordX, player1.coordY, b.coordX, b.coordY);
            if ((5.0 + player1.radius >= distancePlayer1) && b.active && !gameRound) {
                player2.life--;
                b.active = false;
                inverter = true;
            }

            //hitbox player2
            double distancePlayer2 = twoPointsDistance(player2.coordX, player2.coordY, b.coordX, b.coordY);
            if ((5.0 + player2.radius >= distancePlayer2) && b.active && gameRound) {
                player1.life--;
                b.active = false;
                inverter = true;
            }

            if(inverter){
                gameSwitch();
            }

            acel = NEWTON * planeta.mass / twoPointsDistance(b.coordX, b.coordY, planeta.coordX, planeta.coordY);

            if (b.coordY!=planeta.coordY) {
                finalYAceleration += getComposedCoefficient(acel, b.coordX, b.coordY, planeta.coordX, planeta.coordY);
                if (planeta.coordY <= b.coordY && b.coordY < 0) {
                    finalYAceleration *= -1;
                }
                (b).speedY += finalYAceleration;
            }

            if (b.coordX!=planeta.coordX) {
                finalXAceleration = (double) sqrt(acel * acel - finalYAceleration * finalYAceleration);
                if (planeta.coordX <= b.coordX) {
                    finalXAceleration *= -1;
                }
                (b).speedX += finalXAceleration;
            }
        }
    }

    if((hasXgap() || hasYgap()) && b.active){
        b.active = false;
        gameSwitch();
    }

    (b).coordY += b.speedY;
    (b).coordX += b.speedX;

} //acaba o moveball

void gameSwitch(){
    if (gameRound) {
        player1.active = true;
    } else {
        player2.active = true;
    };
    gameRound = !gameRound;
}

void readCreatePlanetsBullets(){
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        al_draw_filled_circle((float) planeta.coordX, (float)  planeta.coordY, (float)  planeta.radius, planeta.color);
    }
    if(b.active) {
        al_draw_filled_circle((float) b.coordX, (float)  b.coordY, 5, WHITE);
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

void setBulletTo(int clickX, int clickY) {

    player1.active = false;
    player2.active = false;
    b.active = true;

    int velInit = 10; // Velocidade inicial

    if(gameRound){
        b.speedY = getComposedCoefficient(velInit, player1.coordX, player1.coordY, clickX, clickY);
        b.speedX = (double) sqrt(velInit*velInit - b.speedY*b.speedY);

        b.coordY = player1.coordY;
        b.coordX = player1.coordX;
        if (clickY<=player1.coordY) {
            b.speedY *= -1;
        }
        if (clickX <= player1.coordX) {
            b.speedX *= -1;
        }
    }else{
        b.speedY = getComposedCoefficient(velInit, player2.coordX, player2.coordY, clickX, clickY);
        b.speedX = (double) sqrt(velInit*velInit - b.speedY*b.speedY);

        b.coordY = player2.coordY;
        b.coordX = player2.coordX;
        if (clickY <= player2.coordY) {
            b.speedY *= -1;
        }
        if (clickX <= player2.coordX) {
            b.speedX *= -1;
        }
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