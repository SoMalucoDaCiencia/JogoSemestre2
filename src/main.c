#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <deps/nossaLivraria.h>

bool FPS_POLARITY = false;
int const WINDOW_WIDTH          = 1280;
int const WINDOW_HEIGHT         = 720;
float const FPS                 = 60;

ALLEGRO_BITMAP *astro, *tittle;
ALLEGRO_FONT *font;

ALLEGRO_COLOR BLACK       ;
ALLEGRO_COLOR WHITE       ;
ALLEGRO_COLOR DARK_PURPLE ;
ALLEGRO_COLOR LIGHT_PURPLE;
ALLEGRO_COLOR RED         ;
ALLEGRO_COLOR YELLOW      ;
ALLEGRO_COLOR LIGHT_GREEN ;
ALLEGRO_COLOR DARK_GREEN  ;
ALLEGRO_COLOR LIGHT_BLUE  ;
ALLEGRO_COLOR DARK_BLUE   ;
ALLEGRO_COLOR PINK        ;
ALLEGRO_COLOR ORANGE      ;
ALLEGRO_COLOR BROWN       ;

void drawManu(ALLEGRO_DISPLAY* display) {
    // TELA DO MENU
    al_clear_to_color(BLACK);
    al_draw_bitmap(astro, 870, 150, 0);
    al_draw_bitmap(tittle, (float)(WINDOW_WIDTH/2)-236, 50, 0);

//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 465, 0, "Play");
//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 555, 0, "Config");
//                      al_draw_text( font, al_map_rgb(88, 43, 66), 200, 625, 0, "Quit");

    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 520, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 600, LIGHT_PURPLE, display);

    printf(" - Drawing MENU....[%s]\n", getNow());
    al_flip_display();
}

void drawConfig(ALLEGRO_DISPLAY* display) {
    // TELA DE CONFIGURAÇÕES
    al_clear_to_color(BLACK);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);

    printf(" - Drawing SETTINGS....[%s]\n", getNow());
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

    // Inicia paleta de cores
    BLACK        = BLACK;
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

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // Inicia eventos criados pelo mouse
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia eventos criados pelo teclado
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Inicia display
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_clear_to_color(BLACK);

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

                        if (ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80) {
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
                al_clear_to_color(BLACK);
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