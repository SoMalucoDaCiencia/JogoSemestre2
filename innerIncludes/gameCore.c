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

Planeta *planetas; // Lista de planetas
MAP activeMap; // Mapa atual sendo usado
Bullet b; // Bolinha

struct User player1 , player2;

int planetaSize; // Quantidade de planetas
bool gameRound; // True == player1 and False == player2
double NEWTON;  // Constante newtoniana
double acel;    // Aceleracao somada da grade

// Inicia as variaveis necessarias do jogo
void initGame() {

    b.speedX = 0;
    b.speedY = 0;
    b.radius = 1;

    readSetPlanet();

    if(getRandomInt(1, 0) == 0) {
        gameRound = true;
    } else {
        gameRound = false;
    }

    player1.character = CAT;
    player1.coordY =  planetas[1].coordY - (planetas[1].radius + 30);
    player1.coordX =  planetas[1].coordX;
    player1.life   = 1;
    player1.radius = 24;

    player2.character = SULLIVAN;
    player2.coordY =  planetas[0].coordY - (planetas[0].radius + 30);
    player2.coordX =  planetas[0].coordX;
    player2.life   = 5;
    player2.radius = 24;

    if (gameRound) {
        b.coordY = player1.coordY;
        b.coordX = player1.coordX;
    } else {
        b.coordY = player2.coordY;
        b.coordX = player2.coordX;
    }

//    NEWTON = 6.6743 * pow(10, -11);
    NEWTON = 6.6743 * innerPow(10, 1);
}

// Encerra uma partida
void finishGame(){
    GAMESTATE = TRANSITION;
    orderRedraw = true;
}

// Processa a gravidade
void moveBall() {

    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        double finalXAceleration = 0;
        double finalYAceleration = 0;

        if(planeta.nome != NULL){
            bool inverter = false;
            //hitbox planeta
            double distance = twoPointsDistance(planeta.coordX, planeta.coordY, b.coordX, b.coordY);
            if ((b.radius + planeta.radius >= distance) && b.active) {
                b.active = false;
                inverter = true;
            }

            //hitbox player1
              double distancePlayer1 = twoPointsDistance(player1.coordX, player1.coordY, b.coordX, b.coordY);
            if ((b.radius + player1.radius >= distancePlayer1) && b.active && !gameRound) {
                player1.life--;
                b.active = false;
                inverter = true;
            }

            //hitbox player2
            double distancePlayer2 = twoPointsDistance(player2.coordX, player2.coordY, b.coordX, b.coordY);
            if ((b.radius + player2.radius >= distancePlayer2) && b.active && gameRound) {
                player2.life--;
                b.active = false;
                inverter = true;
            }

            if(inverter){
                gameRound = !gameRound;
            }

            acel = NEWTON * planeta.mass / twoPointsDistance(b.coordX, b.coordY, planeta.coordX, planeta.coordY);

            if (b.coordY!=planeta.coordY) {
                finalYAceleration += getComposedCoefficient(acel, b.coordX, b.coordY, planeta.coordX, planeta.coordY);
                if (planeta.coordY <= b.coordY) {
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
        gameRound = !gameRound;
    }

    (b).coordY += b.speedY;
    (b).coordX += b.speedX;

} //acaba o moveball

// Renderiza os planetas
void readCreatePlanetsBullets(){

    if (player1.life * player2.life != 0) {
        for (int i = 0; i < planetaSize; ++i) {
            Planeta planeta = planetas[i];
            al_draw_filled_circle((float) planeta.coordX, (float)  planeta.coordY, planeta.radius, planeta.color);
        }

        if(b.active) {
            al_draw_filled_circle((float) b.coordX, (float)  b.coordY, b.radius, WHITE);
        }else {
            al_draw_filled_circle((float)WINDOW_WIDTH * 2, (float) WINDOW_HEIGHT * 2, b.radius, WHITE);
            b.speedX = 0;
            b.speedY = 0;
        }
    }
}

// Mede distancias no mapa com pitagoras
double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY) {
    const int x = (pointAX > pointBX ? (pointAX - pointBX) : (pointBX - pointAX));
    const int y = (pointAY > pointBY ? (pointAY - pointBY) : (pointBY - pointAY));

    return floor(sqrt(pow(x, 2) + pow(y, 2)));
}

// Muda a posicao da bolinha para as coordenadas passadas
void setBulletTo(int clickX, int clickY) {
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