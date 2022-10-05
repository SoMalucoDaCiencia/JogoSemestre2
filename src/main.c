#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <deps/nossaLivraria.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <unistd.h>
#include <allegro5/allegro_primitives.h>
#define background "background.bmp"

int main() {

    al_init();
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();

    ALLEGRO_DISPLAY* display = al_create_display(1280,720);
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //ALLEGRO_BITMAP *image = al_load_bitmap(background);
    //al_draw_bitmap(image, 0, 0, 0);
    //al_destroy_bitmap(image);
    while (true) {
        //handle input and timer
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            //put all fps dependant function here
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
}