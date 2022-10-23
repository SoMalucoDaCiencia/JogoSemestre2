//
// Created by alan_ on 23/10/2022.
//

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <Cores.h>
#include <deps/nossaLivraria.h>

void init_colors(){
    //inicia paleta de cores
    BLACK        = getColorByHex((char*) "#000000");
    WHITE        = getColorByHex((char*) "#ffffff");
    DARK_PURPLE  = getColorByHex((char*) "#491485");
    LIGHT_PURPLE = getColorByHex((char*) "#9547ed");
    RED          = getColorByHex((char*) "#fa2347");
    YELLOW       = getColorByHex((char*) "#ffcc00");
    LIGHT_GREEN  = getColorByHex((char*) "#60d642");
    DARK_GREEN   = getColorByHex((char*) "#143d09");
    LIGHT_BLUE   = getColorByHex((char*) "#477eff");
    DARK_BLUE    = getColorByHex((char*) "#0a2563");
    PINK         = getColorByHex((char*) "#f227de");
    ORANGE       = getColorByHex((char*) "#ff7b00");
    BROWN        = getColorByHex((char*) "#4f2600");
}
