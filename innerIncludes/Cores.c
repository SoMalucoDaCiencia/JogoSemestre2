//
// Created by alan_ on 23/10/2022.
//

#include <stdlib.h>
#include <allegro5/allegro.h>
#include "innerIncludes/headers/Cores.h"
#include "innerIncludes/headers/nossaLivraria.h"

ALLEGRO_COLOR BLACK       ;
ALLEGRO_COLOR WHITE       ;
ALLEGRO_COLOR DARK_PURPLE ;
ALLEGRO_COLOR LIGHT_PURPLE;
ALLEGRO_COLOR RED         ;
ALLEGRO_COLOR YELLOW      ;
ALLEGRO_COLOR GREEN       ;
ALLEGRO_COLOR LIGHT_GREEN ;
ALLEGRO_COLOR DARK_GREEN  ;
ALLEGRO_COLOR BLUE        ;
ALLEGRO_COLOR LIGHT_BLUE  ;
ALLEGRO_COLOR DARK_BLUE   ;
ALLEGRO_COLOR OCEAN_BLUE  ;
ALLEGRO_COLOR PINK        ;
ALLEGRO_COLOR ORANGE      ;
ALLEGRO_COLOR BROWN       ;
ALLEGRO_COLOR GRAY        ;

void init_colors(){
    //inicia paleta de cores
    BLACK        = getColorByHex((char*) "#000000");
    WHITE        = getColorByHex((char*) "#ffffff");
    DARK_PURPLE  = getColorByHex((char*) "#491485");
    LIGHT_PURPLE = getColorByHex((char*) "#9547ed");
    RED          = getColorByHex((char*) "#fa2347");
    YELLOW       = getColorByHex((char*) "#ffcc00");
    GREEN  = getColorByHex((char*) "#8cbb4f");
    LIGHT_GREEN  = getColorByHex((char*) "#60d642");
    DARK_GREEN   = getColorByHex((char*) "#143d09");
    BLUE   = getColorByHex((char*) "#0fc1eb");
    LIGHT_BLUE   = getColorByHex((char*) "#477eff");
    OCEAN_BLUE   = getColorByHex((char*) "#56f1d1");
    DARK_BLUE    = getColorByHex((char*) "#0a2563");
    PINK         = getColorByHex((char*) "#f227de");
    ORANGE       = getColorByHex((char*) "#ff7b00");
    BROWN        = getColorByHex((char*) "#4f2600");
    GRAY         = getColorByHex((char*) "#dccc89");
}
