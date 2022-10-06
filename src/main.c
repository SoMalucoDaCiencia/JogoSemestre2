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

    int gamestate = 0; // STATE INICIAL

    while (true) {

        ALLEGRO_EVENT ev;
        ALLEGRO_BITMAP *play = NULL, *options = NULL, *quit = NULL, *back = NULL;

        al_wait_for_event(event_queue, &ev); // ESPERANDO POR EVENTOS

        switch(ev.type) {

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {

                // EVENTO CLICK

                switch(gamestate) {

                    case 0: {
                        // BOTÕES DO MENU

                        if (ev.mouse.x >= 490 && ev.mouse.x <= 790) {
                            if (ev.mouse.y >= 150 && ev.mouse.y <= 250) {
                                // CLICK BOTÃO PLAY

                                gamestate = 1;
                            } else if (ev.mouse.y >= 300 && ev.mouse.y <= 400) {
                                // CLICK BOTÃO CONFIG

                                gamestate = 2;
                            } else if (ev.mouse.y >= 450 && ev.mouse.y <= 550) {
                                // CLICK BOTÃO QUIT

                                al_destroy_bitmap(play);
                                al_destroy_bitmap(options);
                                al_destroy_bitmap(quit);
                                al_destroy_bitmap(back);
                                killNine(timer, display, event_queue);
                                // ^^ SALVA SEU COMPUTADOR DE EXPLODIR
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

                        if (ev.mouse.x >= 30 && ev.mouse.x <= 150 && ev.mouse.y >= 30 && ev.mouse.y <= 70){

                            gamestate = 0; // RETORNA A TELA DE MENU
                        }
                        break;
                    }

                }

            }
            case ALLEGRO_EVENT_TIMER: {
                FPS_POLARITY = !FPS_POLARITY; // POLARIDADE DO FPS

                if (!al_init_image_addon()) break; // AGUARDA O ADDON DE IMAGEM INICIAR -> SE NÂO TIVER INICIADO NÃO PARTE PARA PRÓXIMA PARTE DO CÓDIGO

                switch(gamestate) {

                    case 0: {
                        // TELA DO MENU

                        al_clear_to_color(al_map_rgb(0, 0, 0));

                        play = al_load_bitmap("../src/assets/play.png");
                        if (play != NULL) {
                            al_draw_bitmap(play, 490, 150, 0); // DRAW DO BOTÃO PLAY
                        }
                        options = al_load_bitmap("../src/assets/options.png");
                        if (options != NULL) {
                            al_draw_bitmap(options, 490, 300, 0); // DRAW DO BOTÃO OPTIONS
                        }
                        quit = al_load_bitmap("../src/assets/quit.png");
                        if (quit != NULL) {
                            al_draw_bitmap(quit, 490, 450, 0); // DRAW DO BOTÃO QUIT
                        }

                        break;
                    }
                    case 1: {
                        // TELA PLAY

                        al_clear_to_color(al_map_rgb(0, 0, 0));

                        break;
                    }
                    case 2: {
                        // TELA CONFIG

                        al_clear_to_color(al_map_rgb(0, 0, 0));

                        back = al_load_bitmap("../src/assets/back.png");
                        if (back != NULL) {
                            al_draw_bitmap(back, 30, 30, 0); // DRAW DO BOTÂO BACK
                        }

                        break;
                    }

                }

                al_flip_display(); // FLIP DISPLAY A TODO FRAME
                break; // BREAK DO EVENTO TIMER

            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                al_destroy_bitmap(play);
                al_destroy_bitmap(options);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(back);
                killNine(timer, display, event_queue);
                break;
                // ^^ SALVA SEU COMPUTADOR DE EXPLODIR
            }

        }

    }

}
