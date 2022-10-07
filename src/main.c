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
#include <allegro5/allegro_font.h>
#include <unistd.h>
#include <allegro5/allegro_primitives.h>

static bool FPS_POLARITY = false;
static int WINDOW_WIDTH = 1280;
static int WINDOW_HEIGHT = 720;
static const float FPS = 60;

int main() {

    al_init();

    // Inicia display
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Inicia fileira de eventos
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

    // Carrrega as imagens da jogo
    ALLEGRO_BITMAP *play, *options, *quit, *back, *astro, *tittle;
    if (al_init_image_addon()) {

        astro = al_load_bitmap("../src/assets/as.png");
        play = al_load_bitmap("../src/assets/play.png");
        options = al_load_bitmap("../src/assets/options.png");
        back = al_load_bitmap("../src/assets/back.png");
        quit = al_load_bitmap("assets/quit.png");
        tittle = al_load_bitmap("../src/assets/tittle.png");
    }

    int GAMESTATE = 0; // STATE INICIAL

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev); // ESPERANDO POR EVENTOS
        switch (ev.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                // EVENTO CLICK

                al_clear_to_color(al_map_rgb(255, 255, 255));
                switch (GAMESTATE) {
                    case 0: {
                        // BOTÕES DO MENU
                        if (ev.mouse.x >= (WINDOW_WIDTH/2)-200 && ev.mouse.x <= (WINDOW_WIDTH/2)+200) {
                            if (ev.mouse.y >= 440 && ev.mouse.y <= 490) {     // play
                                GAMESTATE = 1;
                            } else if (ev.mouse.y >= 520 && ev.mouse.y <= 570) {     // config
                                GAMESTATE = 2;
                            } else if(ev.mouse.y >= 600 && ev.mouse.y <= 670) {             // quit
                                al_destroy_bitmap(play);
                                al_destroy_bitmap(options);
                                al_destroy_bitmap(quit);
                                al_destroy_bitmap(back);
                                al_destroy_bitmap(astro);
                                al_destroy_bitmap(tittle);
                                killNine(timer, display, event_queue);
                            }
                        }
                        break;
                    }
                    case 1: {
                        // BOTÕES DA TELA PLAY

                        break;
                    }
                    case 2: {
                        // BOTÕES DA TELA CONFIG

                        if (ev.mouse.x >= 30 && ev.mouse.x <= 150 && ev.mouse.y >= 30 && ev.mouse.y <= 70) {
                            GAMESTATE = 0; // RETORNA A TELA DE MENU
                        }
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                FPS_POLARITY = !FPS_POLARITY; // POLARIDADE DO FPS
                al_clear_to_color(al_map_rgb(255, 255, 255));
                switch (GAMESTATE) {
                    case 0: {
                        // TELA DO MENU
                        if (al_init_image_addon()) {

                            al_draw_bitmap(astro, 870, 150, 0);
                            al_draw_bitmap(tittle, (WINDOW_WIDTH / 2) - 236, 50, 0);
                        }

////                if (al_init_font_addon()) {
////                    ALLEGRO_FONT *font = al_load_bitmap_font("../src/assets/fonts/Courier-New.tga");
////                    al_draw_text( font, al_map_rgb(88, 43, 66), 200, 465, 0, "Play");
////                    al_draw_text( font, al_map_rgb(88, 43, 66), 200, 555, 0, "Config");
////                    al_draw_text( font, al_map_rgb(88, 43, 66), 200, 625, 0, "Quit");
////                }
//
                        insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
                        insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 520, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
                        insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 600, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
                        break;
                    }
                    case 1: {
                        // TELA PLAY

                        break;
                    }
                    case 2: {
                        // TELA CONFIG
                        if (back != NULL) {
                            al_draw_bitmap(back, 30, 30, 0); // DRAW DO BOTÂO BACK
                        }
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                al_destroy_bitmap(play);
                al_destroy_bitmap(options);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(back);
                al_destroy_bitmap(astro);
                al_destroy_bitmap(tittle);
                killNine(timer, display, event_queue);
                // ^^ SALVA SEU COMPUTADOR DE EXPLODIR
                break;
            }
        }
        al_flip_display();
    }
}