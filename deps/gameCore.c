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

User user1;
//User user2;

float planetaSize;
int bulletsSize;
bool limitWalls;
double NEWTON;
double acel;

void initGame() {

    planetas[0].color = RED;
    planetas[0].nome = "Arthur";
    planetas[0].coordX = WINDOW_WIDTH/2;
    planetas[0].coordY = WINDOW_HEIGHT/2;
    planetas[0].radius = 20;
    planetas[0].mass = 1;

    user1.ID = 1;
    user1.coordY =  WINDOW_HEIGHT/2 - planetas[0].radius;
    user1.coordX =  WINDOW_WIDTH/2;

//    planetas[1].color = DARK_BLUE;
//    planetas[1].nome = "Tais";
//    planetas[1].coordX = 200;
//    planetas[1].coordY = 590;
//    planetas[1].radius = 30;
//    planetas[1].mass = 2;

    planetaSize = sizeof(planetas) / sizeof(Planeta);

    bullets = malloc(0);

//    NEWTON = 6.6743 * pow(10, -11);
    NEWTON = 6.6743 * pow(10, 0);
    limitWalls = false;
}

void moveBall() {
    for (int j = 0; j < bulletsSize; ++j) {

        Bullet* b = &(bullets[j]);
        double finalXAceleration = b->speedX;
        double finalYAceleration = b->speedY;

//        for (int i = 0; i < planetaSize; ++i) {
//            Planeta planeta = planetas[i];
//
//            acel = NEWTON * planeta.mass / twoPointsDistance(b->coordX, b->coordY, planeta.coordX, planeta.coordY);
//            if (planeta.coordY >= b->coordY) {
//                finalYAceleration += acel;
//            } else if (planeta.coordY < b->coordY) {
//                finalYAceleration += acel * (-1);
//            }
//
//            if (planeta.coordX >= b->coordX) {
//                finalXAceleration += acel;
//            } else if (planeta.coordX < b->coordX) {
//                finalXAceleration += acel * (-1);
//            }
//        }
        (b)->coordY += finalYAceleration;
        (b)->coordX += finalXAceleration;

        if (false) {
            if (hasYgap(b->coordY, b->speedY)) {
                b->speedY *= -1;

            }
            if (hasXgap(b->coordX, b->speedX)) {
                b->speedX *= -1;
            }
        }

//        (b)->coordY += floor(b->speedY);
//        (b)->coordX += floor(b->speedX);
    }
} //acaba o moveball

Planeta* scanPlanetsYaml(int level) {

}

void readCreatePlanetsBullets(){
    for (int i = 0; i < planetaSize; ++i) {
        Planeta planeta = planetas[i];
        al_draw_filled_circle((float) planeta.coordX, (float)  planeta.coordY, (float)  planeta.radius, planeta.color);
    }
    for (int i = 0; i < bulletsSize; ++i) {
        Bullet bullet = bullets[i];
        al_draw_filled_circle((float) bullet.coordX, (float)  bullet.coordY, 1.0, WHITE);
    }
}

double twoPointsDistance(int pointAX, int pointAY,int pointBX,int pointBY) {
    const int x = (pointAX > pointBX ? (pointAX - pointBX) : (pointBX - pointAX));
    const int y = (pointAY > pointBY ? (pointAY - pointBY) : (pointBY - pointAY));

    return floor(sqrt(pow(x, 2) + pow(y, 2)));
}

void insertBullet(int clickX, int clickY) {
    User user = user1;
    bullets = realloc(bullets, sizeof(bullets) + sizeof(Bullet));
    bullets[bulletsSize] = initBullet(user.coordX, user.coordY, clickX, clickY, bulletsSize);
    bulletsSize++;
}

void removeBullet(int id) {
    for (int i = 0; i < bulletsSize; ++i) {
        Bullet bullet = bullets[i];
        al_draw_filled_circle((float) bullet.coordX, (float)  bullet.coordY, 1.0, WHITE);
    }
}

Bullet initBullet(int coordX, int coordY, int clickX, int clickY, int id) {
    Bullet ret;
    ret.ID = id;
    ret.coordX = coordX;
    ret.coordY = coordY;

    double m = (((double) clickY - coordY) / ((double) clickX - coordX));
    int velocidadeTiroSaida = 2;
    ret.speedY = sqrt(velocidadeTiroSaida*velocidadeTiroSaida / (1 + m*m));
    ret.speedX = ret.speedY * m;

    // Correcao do bug e mapas
    if (clickX <= coordX) {
        ret.speedX *= -1;
    }

    return ret;
};

// Verifica se a bolinha vai bater na esquerda ou na direita
bool hasXgap(int coordx, double speedX) {
    if (speedX>0) {
        return (round(coordx + speedX + 1.0) >= WINDOW_WIDTH);
    } else {
        return (floor(coordx - speedX - 1.0) <= 0);
    }
}

// Verifica se a bolinha vai bater no teto ou no chao
bool hasYgap(int coordy, double speedY) {
    if (speedY>0) {
        return (round(coordy + speedY + 1.0) >= WINDOW_HEIGHT);
    } else {
        return (floor(coordy - speedY - 1.0) <= 0);
    }
}



