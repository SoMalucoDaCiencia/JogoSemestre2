//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>
#include <allegro5/display.h>
#include <innerIncludes/headers/Suporte.h>


#ifndef JOGOSEMESTRE2_LIVRARIA_H
#define JOGOSEMESTRE2_LIVRARIA_H

    char* isMAC();

    void clearConsole();

    int println (const String format, ...);

    String readFile(String fileName);

    char* getNow();

    int getRandomInt(int max, int min);

    void insertFilledSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display);

    void insertSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display, int borderSize, ALLEGRO_COLOR borderColor);

//    double root(int basis, int exponent);

    double innerPow(double basis, int exponent);

    ALLEGRO_COLOR getColorByHex(char* hexColor);

    double getComposedCoefficient(double force, int pointAX, int pointAY,int pointBX,int pointBY);

    void waitTime(unsigned int t);

    int err(const String format, ...);

#endif //JOGOSEMESTRE2_LIVRARIA_H
