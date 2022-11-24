//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <stdio.h>

bool isMAC() {
#ifdef __APPLE__
    return 1;
#endif
    return 0;
}

char* getNow() {
    time_t rawtime;
    time(&rawtime);

    char* now =  asctime(localtime(&rawtime));
    now[strcspn(now, "\n")] = 0; // Tira quebra de linha do final da string
    return now;
}

int getRandomInt(int max, int min) {
    return (rand() % (max - min + 1)) + min;
}

void insertFilledSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display) {
    ALLEGRO_BITMAP *square = al_create_bitmap(width, height);
    al_set_target_bitmap(square);
    al_clear_to_color(color);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(square, x, y, 0);
    al_destroy_bitmap(square);
}

void insertShadowSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_COLOR shadowColor, ALLEGRO_DISPLAY *display) {
    insertFilledSquare(height, width, x+10, y+10, shadowColor, display);
    insertFilledSquare(height, width, x, y, color, display);
}

ALLEGRO_COLOR const getColorByHex(char* hexStringValue) {
    int r, g, b;
    sscanf(hexStringValue, "#%02x%02x%02x", &r, &g, &b);
    return al_map_rgb(r, g, b);
}

void insertSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display, int borderSize, ALLEGRO_COLOR borderColor) {
    if (borderSize>0) {
        insertFilledSquare(height + borderSize, width + borderSize, x, y, borderColor, display);
    }
    insertFilledSquare(height, width, x + (borderSize/2), y + (borderSize/2), color, display);
}