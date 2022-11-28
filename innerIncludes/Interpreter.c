//
// Created by tais on 25/11/2022.
//

#include <stdlib.h>
#include <innerIncludes/headers/Suporte.h>
#include <innerIncludes/headers/Interpreter.h>
#include <innerIncludes/headers/nossaLivraria.h>
#include <innerIncludes/headers/gameCore.h>


// Pega o caminho para o arquivo do mapa
String getMaps(MAP mapsList){
    switch(mapsList){
        case MAP1: {
            return "../src/assets/mapas/mapa1.yaml";
            break;
        }
        case MAP2: {
            return "../src/assets/mapas/mapa2.yaml";
            break;
        }
        case MAP3: {
            return "../src/assets/mapas/mapa3.yaml";
            break;
        }
        default: {
            err("Esse mapa não existe.");
        }
    }
}

// Interpreta os mapas em .yaml e cria os planetas
void readSetPlanet(){
    int here = 0;
    int planeta = -1;
    int qtdPlanetas = 0;
    String code = readFile(getMaps(activeMap));

    // Conta quantos planetas (--) tem
    for(int k = 0; code[k] != '\0'; k++){
        if(code[k] == '-'){
            qtdPlanetas++;
        }
    }
    planetaSize = qtdPlanetas/2;

    // Lê, conta e inicializa quantos planetas tem
    planetas = (Planeta*) malloc(sizeof(Planeta) * (planetaSize));

    while(code[here] != '\0'){
        // Pula espaços e tabs
        if(code[here] == ' ' || code[here] == '\t') {
            here++;
            continue;
        }

        switch(code[here]){
            case 'c': {
                int stringStartAt = here + 3;
                while(code[here] != '\n'){
                    here++;
                }
                String getColor;
                getColor = substring(code, stringStartAt, here);
                planetas[planeta].color = getColorByHex(getColor);
                free(getColor);
                break;
            }
            case '-': {
                here++;
                int stringStartAt = here;
                while(code[here] != '-'){
                    here++;
                }
                planeta++;
                planetas[planeta].nome = substring(code, stringStartAt, here);
                here += 2;
                break;
            }
            case 'r': {
                int stringStartAt = here + 3;
                while(code[here] != '\n'){
                    here++;
                }
                String getRadius;
                getRadius = substring(code, stringStartAt, here);
                planetas[planeta].radius = IntString(getRadius);
                free(getRadius);
                break;
            }
            case 'm': {
                int stringStartAt = here + 3;
                while(code[here] != '\n'){
                    here++;
                }
                String getMass = substring(code, stringStartAt, here);
                planetas[planeta].mass = doubleString(getMass);
                free(getMass);
                break;
            }
            case 'x': {
                int stringStartAt = here + 3;
                while(code[here] != '\n'){
                    here++;
                }
                String getCoordX = substring(code, stringStartAt, here);
                planetas[planeta].coordX = IntString(getCoordX);
                free(getCoordX);
                break;
            }
            case 'y': {
                int stringStartAt = here + 3;
                while(code[here] != '\n'){
                    here++;
                }
                String getCoordY = substring(code, stringStartAt, here);
                planetas[planeta].coordY = IntString(getCoordY);
                free(getCoordY);
                break;
            }
            default: {
                here++;
            }
        }
    }
    free(code);
}

void setMap1() {
    if (planetaSize>0) {
//        for (int i = 0; i < planetaSize; ++i) {
//            free(planetas[i].nome);
//        }
        planetaSize = 0;
        free(planetas);
    }
    planetaSize = 3;
    planetas = (Planeta*) malloc(sizeof(Planeta) * 3);
    planetas[0].nome = "p1";
    planetas[0].radius = 20;
    planetas[0].mass = 0.12;
    planetas[0].coordX = 1180;
    planetas[0].coordY = 360;
    planetas[0].color = getColorByHex("#fa2347");

    planetas[1].nome = "p2";
    planetas[1].radius = 20;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 140;
    planetas[1].coordY = 360;
    planetas[1].color = getColorByHex("#ffffff");

    planetas[2].nome = "p1";
    planetas[2].radius = 45;
    planetas[2].mass = 0.6;
    planetas[2].coordX = 640;
    planetas[2].coordY = 360;
    planetas[2].color = getColorByHex("#6e34eb");
}

void setMap2() {
    if (planetaSize>0) {
//        for (int i = 0; i < planetaSize; ++i) {
//            free(planetas[i].nome);
//        }
        planetaSize = 0;
        free(planetas);
    }
    planetaSize = 5;
    planetas = (Planeta*) malloc(sizeof(Planeta) * 5);
    planetas[0].nome = "p1";
    planetas[0].radius = 20;
    planetas[0].mass = 0.12;
    planetas[0].coordX = 1180;
    planetas[0].coordY = 360;
    planetas[0].color = getColorByHex("#fa2347");

    planetas[1].nome = "p2";
    planetas[1].radius = 20;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 140;
    planetas[1].coordY = 360;
    planetas[1].color = getColorByHex("#ffffff");

    planetas[2].nome = "p3";
    planetas[2].radius = 35;
    planetas[2].mass = 0.32;
    planetas[2].coordX = 400;
    planetas[2].coordY = 100;
    planetas[2].color = getColorByHex("#fcba03");

    planetas[3].nome = "p4";
    planetas[3].radius = 10;
    planetas[3].mass = 0.12;
    planetas[3].coordX = 550;
    planetas[3].coordY = 350;
    planetas[3].color = getColorByHex("#45a3a0");

    planetas[4].nome = "p5";
    planetas[4].radius = 35;
    planetas[4].mass = 0.32;
    planetas[4].coordX = 400;
    planetas[4].coordY = 600;
    planetas[4].color = getColorByHex("#9c0e7d");
}

void setMap3() {

}


