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
    planetas[0].color = getColorByHex("#1a5d64"); //ciano escuro

    planetas[1].nome = "p2";
    planetas[1].radius = 20;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 140;
    planetas[1].coordY = 360;
    planetas[1].color = getColorByHex("#42bcb6"); //ciano claro

    planetas[2].nome = "p3";
    planetas[2].radius = 55;
    planetas[2].mass = 0.6;
    planetas[2].coordX = 640;
    planetas[2].coordY = 370;
    planetas[2].color = getColorByHex("#24341c"); //verde escuro
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
    planetas[0].radius = 30;
    planetas[0].mass = 0.12;
    planetas[0].coordX = 1120;
    planetas[0].coordY = 380;
    planetas[0].color = getColorByHex("#4e5f97"); //azul meio roxo

    planetas[1].nome = "p2";
    planetas[1].radius = 30;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 180;
    planetas[1].coordY = 335;
    planetas[1].color = getColorByHex("#7287b9"); //azul meio roxo claro

    planetas[2].nome = "p3";
    planetas[2].radius = 45;
    planetas[2].mass = 0.32;
    planetas[2].coordX = 500;
    planetas[2].coordY = 160;
    planetas[2].color = getColorByHex("#28304f"); //roxo bem escuro

    planetas[3].nome = "p4";
    planetas[3].radius = 35;
    planetas[3].mass = 0.32;
    planetas[3].coordX = 715;
    planetas[3].coordY = 320;
    planetas[3].color = getColorByHex("#c29991"); //pele

    planetas[4].nome = "p5";
    planetas[4].radius = 45;
    planetas[4].mass = 0.32;
    planetas[4].coordX = 480;
    planetas[4].coordY = 560;
    planetas[4].color = getColorByHex("#8ca6cc"); //azul claro
}

void setMap3() {
    if (planetaSize>0) {
//        for (int i = 0; i < planetaSize; ++i) {
//            free(planetas[i].nome);
//        }
        planetaSize = 0;
        free(planetas);
    }

    planetaSize = 6;
    planetas = (Planeta*) malloc(sizeof(Planeta) * 6);
    planetas[0].nome = "p1";
    planetas[0].radius = 30;
    planetas[0].mass = 0.32;
    planetas[0].coordX = 1030;
    planetas[0].coordY = 600;
    planetas[0].color = getColorByHex("#83b6d1"); //azul claro

    planetas[1].nome = "p2";
    planetas[1].radius = 30;
    planetas[1].mass = 0.32;
    planetas[1].coordX = 230;
    planetas[1].coordY = 220;
    planetas[1].color = getColorByHex("#6ba492"); //verde agua

    planetas[2].nome = "p3";
    planetas[2].radius = 55;
    planetas[2].mass = 0.32;
    planetas[2].coordX = 615;
    planetas[2].coordY = 430;
    planetas[2].color = getColorByHex("#2a4f47"); //verde escuro

    planetas[3].nome = "p4";
    planetas[3].radius = 20;
    planetas[3].mass = 0.12;
    planetas[3].coordX = 310;
    planetas[3].coordY = 400;
    planetas[3].color = getColorByHex("#d04b4d"); //coral

    planetas[4].nome = "p5";
    planetas[4].radius = 35;
    planetas[4].mass = 0.12;
    planetas[4].coordX = 760;
    planetas[4].coordY = 210;
    planetas[4].color = getColorByHex("#ab5031"); //laranja

    planetas[5].nome = "p6";
    planetas[5].radius = 35;
    planetas[5].mass = 0.32;
    planetas[5].coordX = 1095;
    planetas[5].coordY = 180;
    planetas[5].color = getColorByHex("#c46b6c"); //rosa
}

void setMap4() {
    if (planetaSize>0) {
//        for (int i = 0; i < planetaSize; ++i) {
//            free(planetas[i].nome);
//        }
        planetaSize = 0;
        free(planetas);
    }

    planetaSize = 6;
    planetas = (Planeta*) malloc(sizeof(Planeta) * 6);
    planetas[0].nome = "p1";
    planetas[0].radius = 30;
    planetas[0].mass = 0.12;
    planetas[0].coordX = 380;
    planetas[0].coordY = 200;
    planetas[0].color = getColorByHex("#bc4231"); //vermelho

    planetas[1].nome = "p2";
    planetas[1].radius = 30;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 795;
    planetas[1].coordY = 600;
    planetas[1].color = getColorByHex("#3d221a"); //marrom escuro

    planetas[2].nome = "p3";
    planetas[2].radius = 40;
    planetas[2].mass = 0.32;
    planetas[2].coordX = 660;
    planetas[2].coordY = 380;
    planetas[2].color = getColorByHex("#d09a7e"); //bege

    planetas[3].nome = "p4";
    planetas[3].radius = 55;
    planetas[3].mass = 0.32;
    planetas[3].coordX = 280;
    planetas[3].coordY = 360;
    planetas[3].color = getColorByHex("#a05b44"); //marrom claro

    planetas[4].nome = "p5";
    planetas[4].radius = 20;
    planetas[4].mass = 0.12;
    planetas[4].coordX = 570;
    planetas[4].coordY = 100;
    planetas[4].color = getColorByHex("#76402c"); //marrom medio

    planetas[5].nome = "p6";
    planetas[5].radius = 35;
    planetas[5].mass = 0.32;
    planetas[5].coordX = 1140;
    planetas[5].coordY = 360;
    planetas[5].color = getColorByHex("#c45542"); //coral
}

void setMap5() {
    if (planetaSize>0) {
//        for (int i = 0; i < planetaSize; ++i) {
//            free(planetas[i].nome);
//        }
        planetaSize = 0;
        free(planetas);
    }

    planetaSize = 7;
    planetas = (Planeta*) malloc(sizeof(Planeta) * 7);
    planetas[0].nome = "p1";
    planetas[0].radius = 30;
    planetas[0].mass = 0.12;
    planetas[0].coordX = 1120;
    planetas[0].coordY = 380;
    planetas[0].color = getColorByHex("#bd639b"); //rosa

    planetas[1].nome = "p2";
    planetas[1].radius = 30;
    planetas[1].mass = 0.12;
    planetas[1].coordX = 400;
    planetas[1].coordY = 220;
    planetas[1].color = getColorByHex("#ad9579"); //areia

    planetas[2].nome = "p3";
    planetas[2].radius = 55;
    planetas[2].mass = 0.32;
    planetas[2].coordX = 640;
    planetas[2].coordY = 370;
    planetas[2].color = getColorByHex("#a57d8f"); //rosa escuro

    planetas[3].nome = "p3";
    planetas[3].radius = 45;
    planetas[3].mass = 0.32;
    planetas[3].coordX = 800;
    planetas[3].coordY = 160;
    planetas[3].color = getColorByHex("#f4d7c1"); //areia claro

    planetas[4].nome = "p4";
    planetas[4].radius = 20;
    planetas[4].mass = 0.12;
    planetas[4].coordX = 310;
    planetas[4].coordY = 400;
    planetas[4].color = getColorByHex("#6c4b54"); //vinho

    planetas[5].nome = "p1";
    planetas[5].radius = 30;
    planetas[5].mass = 0.12;
    planetas[5].coordX = 230;
    planetas[5].coordY = 200;
    planetas[5].color = getColorByHex("#f7cedc"); //rosa claro

    planetas[6].nome = "p4";
    planetas[6].radius = 45;
    planetas[6].mass = 0.22;
    planetas[6].coordX = 980;
    planetas[6].coordY = 560;
    planetas[6].color = getColorByHex("#86453d"); //terra
}


