//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>
#include <allegro5/display.h>


#ifndef JOGOSEMESTRE2_LIVRARIA_H
#define JOGOSEMESTRE2_LIVRARIA_H

    char* isMAC();

    char* getNow();

    void insertFilledSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display);

    void insertSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display, int borderSize, ALLEGRO_COLOR borderColor);

    ALLEGRO_COLOR getColorByHex(char* hexColor);

    void killNine(struct ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE *event_queue);

#endif //JOGOSEMESTRE2_LIVRARIA_H
