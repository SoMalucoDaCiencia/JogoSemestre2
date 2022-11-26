//
// Created by tais on 25/11/2022.
//

#ifndef JOGOSEMESTRE2_INTERPRETER_H
#define JOGOSEMESTRE2_INTERPRETER_H

#include <innerIncludes/headers/Suporte.h>

typedef enum {
    MAP1,
    MAP2,
    MAP3
} MAP;

String getMap(MAP mapsList);

void readSetPlanet();

#endif //JOGOSEMESTRE2_INTERPRETER_H
