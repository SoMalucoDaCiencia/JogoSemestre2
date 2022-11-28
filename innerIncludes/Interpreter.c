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

    while(code[here]){
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
                String getColor = substring(code, stringStartAt, here);
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
                String getRadius = substring(code, stringStartAt, here);
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
}


