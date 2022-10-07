//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <unistd.h>
#include <allegro5/allegro_primitives.h>

bool isMAC() {
#ifdef __APPLE__
    return 1;
#endif
    return 0;
}

void insertFilledSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display) {
    ALLEGRO_BITMAP *square = al_create_bitmap(width, height);
    al_set_target_bitmap(square);
    al_clear_to_color(color);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(square, x, y, 0);
    al_destroy_bitmap(square);
}

void insertSquare(int height, int width, int x, int y, ALLEGRO_COLOR color, ALLEGRO_DISPLAY *display, int borderSize, ALLEGRO_COLOR borderColor) {
    if (borderSize>0) {
        insertFilledSquare(height + borderSize, width + borderSize, x, y, borderColor, display);
    }
    insertFilledSquare(height, width, x + (borderSize/2), y + (borderSize/2), color, display);
}

void killNine(ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE *event_queue) {
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    exit(0);
}