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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

static bool FPS_POLARITY = false;
static const float FPS = 60;

int main() {

    al_init();

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_DISPLAY* display = al_create_display(1280,720);

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // Inicia loops por FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // Inicia eventos criados pelo mouse
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia eventos criados pelo teclado
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    while (true) {
        ALLEGRO_EVENT ev;
        ALLEGRO_BITMAP *background, *play, *options, *quit;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
//                printf("Click\n");
//                printf("%d\n",ev.mouse.x);

                if (ev.mouse.x >= 490 && ev.mouse.x <= 790) {

                    if(ev.mouse.y >= 450 && ev.mouse.y <= 550) {             // quit
                        al_destroy_timer(timer);
                        al_destroy_event_queue(event_queue);
                        al_destroy_display(display);
                        exit(0);
                    } else if (ev.mouse.y >= 300 && ev.mouse.y <= 400) {     // config
                        printf("config\n");
                    } else if (ev.mouse.y >= 150 && ev.mouse.y <= 300) {     // play
                        printf("play\n");
                    }

                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                FPS_POLARITY = !FPS_POLARITY;
//                background = al_load_bitmap("assets/background.png");
//                al_draw_bitmap(background,0,0,0);
                insertSquare(100, 300, 490, 150, al_map_rgb(237, 66, 69), display);
                insertSquare(100, 300, 490, 300, al_map_rgb(237, 66, 69), display);
                insertSquare(100, 300, 490, 450, al_map_rgb(237, 66, 69), display);
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                al_destroy_timer(timer);
                al_destroy_event_queue(event_queue);
                al_destroy_display(display);
                exit(0);
            }
        }
    }
}