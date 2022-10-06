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
        al_wait_for_event(event_queue, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {

                if (ev.mouse.x >= 490 && ev.mouse.x <= 790) {
                    if (ev.mouse.y >= 150 && ev.mouse.y <= 250) {     // play
                        printf("start play\n");
                    } else if (ev.mouse.y >= 300 && ev.mouse.y <= 400) {     // config
                        printf("start config\n");
                    } else if(ev.mouse.y >= 450 && ev.mouse.y <= 550) {             // quit
                        killNine(timer, display, event_queue);
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                FPS_POLARITY = !FPS_POLARITY;
                if (al_init_image_addon()) {
//                    ALLEGRO_BITMAP *bg = al_load_bitmap("../src/assets/background.png");
//                    al_draw_bitmap(bg, 0, 0, 0);
                    ALLEGRO_BITMAP *play = al_load_bitmap("../src/assets/play.png");
                    al_draw_bitmap(play, 490, 150, 0);
                    ALLEGRO_BITMAP *options = al_load_bitmap("../src/assets/options.png");
                    al_draw_bitmap(options, 490, 300, 0);
                    ALLEGRO_BITMAP *quit = al_load_bitmap("../src/assets/quit.png");
                    al_draw_bitmap(quit, 490, 450, 0);
                }
                al_flip_display();
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                killNine(timer, display, event_queue);
                break;
            }
        }
    }
}