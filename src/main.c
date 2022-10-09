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

ALLEGRO_BITMAP *astro, *tittle;
ALLEGRO_FONT *font;

void drawManu(ALLEGRO_DISPLAY* display) {
    // TELA DO MENU
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(astro, 870, 150, 0);
    al_draw_bitmap(tittle, (float)(WINDOW_WIDTH/2)-236, 50, 0);

//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 465, 0, "Play");
//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 555, 0, "Config");
//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 625, 0, "Quit");

    insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
    insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 520, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
    insertSquare(50, 400, (WINDOW_WIDTH/2)-200, 600, al_map_rgb(255, 255, 255), display, 6, al_map_rgb(88, 43, 66));
    al_flip_display();
}

void drawConfig(ALLEGRO_DISPLAY* display) {
    // TELA DE CONFIGURAÇÕES
    al_clear_to_color(al_map_rgb(255, 255, 255));
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, al_map_rgb(255, 255, 255), display);
    al_flip_display();
}

int main() {

    // Inicia allegro
    al_init();

    // Carrrega as imagens da jogo
    if (al_init_image_addon()) {
        astro = al_load_bitmap("../src/assets/as.png");
        tittle = al_load_bitmap("../src/assets/tittle.png");
    }

    // Carrrega as fontes da jogo
    if (al_init_font_addon()) {
        font = al_load_bitmap_font("../src/assets/fonts/Courier-New.tga");
    }

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // Inicia eventos criados pelo mouse
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia eventos criados pelo teclado
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Inicia display
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Inicia loops por FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    int GAMESTATE = 0; // STATE INICIAL
    bool orderRedraw = true;

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev); // ESPERANDO POR EVENTOS
        switch (ev.type) {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {

                // EVENTO CLICK
                switch (GAMESTATE) {
                    case 0: {
                        // BOTÕES DO MENU
                        if (ev.mouse.x >= (WINDOW_WIDTH/2)-200 && ev.mouse.x <= (WINDOW_WIDTH/2)+200) {
                            if (ev.mouse.y >= 440 && ev.mouse.y <= 490) {     // play
                                orderRedraw = true;
                                GAMESTATE = 1;
                            } else if (ev.mouse.y >= 520 && ev.mouse.y <= 570) {     // config
                                orderRedraw = true;
                                GAMESTATE = 2;
                            } else if(ev.mouse.y >= 600 && ev.mouse.y <= 670) {             // quit
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
                            orderRedraw = true;
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
                        if (orderRedraw) {
                            drawManu(display);
                            orderRedraw = false;
                        }
                        break;
                    }
                    case 1: {
                        // TELA PLAY

                        break;
                    }
                    case 2: {
                        // TELA CONFIG
                        if (orderRedraw) {
                            drawConfig(display);
                            orderRedraw = false;
                        }
                        break;
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                al_destroy_bitmap(astro);
                al_destroy_bitmap(tittle);
                killNine(timer, display, event_queue);
                // ^^ SALVA SEU COMPUTADOR DE EXPLODIR
                break;
            }
        }
    }
}