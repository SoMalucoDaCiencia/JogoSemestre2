//
// Created by tais on 25/11/2022.
//

#ifndef JOGOSEMESTRE2_INTERPRETER_H
#define JOGOSEMESTRE2_INTERPRETER_H

#include <innerIncludes/headers/Suporte.h>

typedef enum {
    MAP1,
    MAP2,
    MAP3,
    MAP4
} MAP;

String getMap(MAP mapsList);

void readSetPlanet();

void setMap1();

void setMap2();

void setMap3();

void setMap4();

#endif //JOGOSEMESTRE2_INTERPRETER_H
