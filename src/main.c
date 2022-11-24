
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <src/main.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "innerIncludes/headers/nossaLivraria.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "innerIncludes/headers/Cores.h"
#include "innerIncludes/headers/gameCore.h"
#include "outIncludes/headers/algif.h"
#include "innerIncludes/headers/sprites.h"


// ========== Window VARS ===========================================
int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 720;
bool LIMIT_WALLS = false;
// =================================================================

// ========== Frame VARS ===========================================
bool GAME_FREQUENCY_POLARITY = false;
float const GAME_FREQUENCY = 60; // Quantos ciclos de atualizacao acontecem no jogo
// ==================================================================

ALLEGRO_BITMAP *astro, *tittleWorbit, *tittleWelcome, *lifeHeart;
ALLEGRO_EVENT_QUEUE *event_queue, *timer_queue;
ALLEGRO_FONT *font25, *font90, *font45;
ALLEGRO_DISPLAY *display;
ALGIF_ANIMATION *tuto;
ALLEGRO_TIMER *timer;

GAMEMODE GAMESTATE;
bool orderRedraw = true;

//INSTRUÇÕES DO CHARACTER SELECTION
bool whichPlayer;


int main() {

    // Inicia allegro
    al_init();

    // Inicia paleta de cores
    init_colors();

    // Carrega as imagens do jogo
    if (al_init_image_addon()) {
        loadSprites();
        astro = al_load_bitmap("../src/assets/astronauta.png");
        tittleWorbit = al_load_bitmap("../src/assets/worbit.png");
        tittleWelcome = al_load_bitmap("../src/assets/welcome.png");
    }

//    const char *gif = "../src/assets/tutorial/giphy.gif";
//    tuto = algif_load_animation(gif);


    // Inicia biblioteca de primitives
    al_init_primitives_addon();

    // Carrega as fontes do jogo
    if (al_init_font_addon() && al_init_ttf_addon()) {
        font25 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 25, 0);
        font45 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 45, 0);
        font90 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 90, 0);
    }

    // Inicia constante de newton
    initGame();

    // Inicia pilha de eventos do allegro
    event_queue = al_create_event_queue();
    timer_queue = al_create_event_queue();

    // Inicia event listener do mouse
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia event listener do teclado
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Inicia display
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_clear_to_color(BLACK);

    // Inicia loops por GAME_FREQUENCY
    timer = al_create_timer(1.0 / GAME_FREQUENCY);
    al_register_event_source(timer_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    //PERSONAGENS DEFAULT
    player1.character = CAT;
    player2.character = DEMON;

    while (1) {
        ALLEGRO_EVENT ev;

        do {
            al_wait_for_event(event_queue, &ev); // ESPERANDO POR EVENTOS
            if (ev.type != ALLEGRO_EVENT_MOUSE_AXES) {
                eventHandler(ev);
                render(ev);
            }
        } while (!al_is_event_queue_empty(event_queue));

        while (al_is_event_queue_empty(event_queue)) {
            al_wait_for_event(timer_queue, &ev); // ESPERANDO POR EVENTOS
            render(ev);
        }
    }
}

void eventHandler(ALLEGRO_EVENT ev) {

    switch (ev.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {

            // EVENTO CLICK
            switch (GAMESTATE) {
                case MENU: {
                    // BOTÕES DO MENU
                    if (ev.mouse.x >= (WINDOW_WIDTH / 2) - 200 && ev.mouse.x <= (WINDOW_WIDTH / 2) + 200) {
                        if (ev.mouse.y >= 440 && ev.mouse.y <= 490) {     // play
                            orderRedraw = true;
                            GAMESTATE = TUTORIAL;
                        } else if (ev.mouse.y >= 520 && ev.mouse.y <= 570) {     // config
                            orderRedraw = true;
                            GAMESTATE = CONFIG;
                        } else if (ev.mouse.y >= 600 && ev.mouse.y <= 670) {             // quit
                            killNine();
                        }
                    }
                    break;
                }
                case PLAY: {
                    // BOTÕES DA TELA PLAY
                    if (!b.active) {
                        setBulletTo(ev.mouse.x, ev.mouse.y);
                    }

                    break;
                }
                case TUTORIAL: {
                    if (ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80) {
                        orderRedraw = true;
                        GAMESTATE = PLAY; // RETORNA A TELA DE MENU
                    }
                    break;
                }
                case CONFIG: {
                    // BOTÕES DA TELA CONFIG
                    if (ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80) {
                        orderRedraw = true;
                        GAMESTATE = MENU; // RETORNA A TELA DE MENU
                    } else if (ev.mouse.x >= 270 && ev.mouse.x <= 1020 && ev.mouse.y >= 180 && ev.mouse.y <= 300) {
                        orderRedraw = true;
                        GAMESTATE = CHARACTER; //VAI PARA TELA DE SELEÇÃO DE PERSONAGEM
                    }
                    break;
                }
                case CHARACTER: {
                    // BOTÕES DA TELA CONFIG
                     if(ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80){
                        orderRedraw = true;
                        GAMESTATE = CONFIG; //RETORNA PARA AS CONFIGURAÇÕES
                     } else {
                         if (ev.mouse.x >= 410 && ev.mouse.x <= 610) {
                             if (ev.mouse.y >= 160 && ev.mouse.y <= 200) {
                                 player1.character = (SPRITE) (player1.character + 1);
                                 drawCharacterSelection(false);
                             } else if (ev.mouse.y >= 490 && ev.mouse.y <= 540) {
                                 player1.character = (SPRITE) (player1.character - 1);
                                 drawCharacterSelection(false);
                             }
                         }
                         if (ev.mouse.x >= 710 && ev.mouse.x <= 910) {
                             if (ev.mouse.y >= 160 && ev.mouse.y <= 200) {
                                 player2.character = (SPRITE) (player1.character + 1);
                                 drawCharacterSelection(false);
                             } else if (ev.mouse.y >= 490 && ev.mouse.y <= 540) {
                                 player2.character = (SPRITE) (player1.character - 1);
                                 drawCharacterSelection(false);
                             }
                         }
                     }
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {
            if (ev.keyboard.keycode == 59) {
                orderRedraw = true;
                GAMESTATE = MENU; // RETORNA A TELA DE MENU
            }
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
            killNine();
            break;
        }
    }
}

void render(ALLEGRO_EVENT ev) {
    if (ev.type == ALLEGRO_EVENT_TIMER) {
        GAME_FREQUENCY_POLARITY = !GAME_FREQUENCY_POLARITY; // POLARIDADE DO GAME_FREQUENCY
        switch (GAMESTATE) {
            case MENU: {
                if (orderRedraw) {
                    drawMenu();
                    orderRedraw = false;
                }
                break;
            }
            case PLAY: {
                drawGame();
                break;
            }
            case TUTORIAL: {
                if (GAME_FREQUENCY_POLARITY) {
                    drawTutorial();
                    if (orderRedraw) {
                        printf(" - Drawing Tutorial....[%s]\n", getNow());
                        orderRedraw = false;
                    }
                }
                break;
            }
            case CONFIG: {
                // TELA CONFIG
                if (orderRedraw) {
                    drawConfig();
                    orderRedraw = false;
                }
                break;
            }
            case CHARACTER: {
                // TELA PERSONAGENS
                if (orderRedraw) {
                    drawCharacterSelection(true);
                    orderRedraw = false;
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

void drawStars() {

    for (int i = 0; i < 90; ++i) {
        int randomX = getRandomInt(WINDOW_WIDTH, 0);
        int randomY = getRandomInt(WINDOW_HEIGHT, 0);
        int randomR = getRandomInt(4, 0);
        al_draw_filled_circle((float) randomX, (float) randomY, (float) randomR, WHITE);
    }
}

void drawMenu() {
    // TELA DO MENU
    al_clear_to_color(BLACK);

    //DESENHA ESTRELAS
    drawStars();

    //OPÇÕES MENU
    insertShadowSquare(50, 400, (WINDOW_WIDTH / 2) - 200, 440, LIGHT_PURPLE, DARK_PURPLE, display);
    insertShadowSquare(50, 400, (WINDOW_WIDTH / 2) - 200, 520, LIGHT_PURPLE, DARK_PURPLE, display);
    insertShadowSquare(50, 400, (WINDOW_WIDTH / 2) - 200, 600, LIGHT_PURPLE, DARK_PURPLE, display);

    //FONTE MENU
    al_draw_text(font25, WHITE, (float) (WINDOW_WIDTH / 2.0) - 30, 455, 0, "Play");
    al_draw_text(font25, WHITE, (float) (WINDOW_WIDTH / 2.0) - 42, 535, 0, "Config");
    al_draw_text(font25, WHITE, (float) (WINDOW_WIDTH / 2.0) - 30, 615, 0, "Quit");

    //IMAGENS MENU
    al_draw_bitmap(astro, 870, 150, 0);
    al_draw_bitmap(tittleWorbit, (float) (WINDOW_WIDTH / 2.0) - 250, 80, 0);
    insertFilledSquare(17, 150, (WINDOW_WIDTH / 2) - 75, 30, BLACK, display);
    al_draw_bitmap(tittleWelcome, (float) (WINDOW_WIDTH / 2.0) - 75, 30, 0);

    printf(" - Drawing MENU....[%s]\n", getNow());
    al_flip_display();
}

void drawTutorial() {
// TELA DE TUROTIAL
    al_clear_to_color(BLACK);

//    al_draw_bitmap(algif_get_bitmap(tuto, al_get_time()), WINDOW_WIDTH/2 - 110, WINDOW_HEIGHT/2 - 110, 0);

    insertFilledSquare(50, 200, 40, 40, DARK_PURPLE, display);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);

    al_draw_text(font25, WHITE, 90, 40, 0, "Skip");

    al_flip_display();
}


void drawConfig() {
    // TELA DE CONFIGURAÇÕES
    al_clear_to_color(BLACK);

    drawStars();

    insertShadowSquare(50, 200, 30, 30, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 90, 40, 0, "Back");

    insertShadowSquare(120, 750, 270, 180, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font45, WHITE, 360, 220, 0, "CHARACTER SELECTION");

    insertShadowSquare(120, 750, 270, 350, LIGHT_PURPLE, DARK_PURPLE, display);

    insertShadowSquare(120, 750, 270, 520, LIGHT_PURPLE, DARK_PURPLE, display);

    printf(" - Drawing SETTINGS....[%s]\n", getNow());
    al_flip_display();
}

//TELA DE SELEÇÃO DE PERSONAGEM
void drawCharacterSelection(bool all) {

    al_clear_to_color(BLACK);

    insertShadowSquare(50, 200, 30, 30, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 90, 40, 0, "Back");
//
    insertShadowSquare(40, 200, 410, 35, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 446, 40, 0, "PLAYER 1");

    insertShadowSquare(40, 200, 410, 160, LIGHT_PURPLE, DARK_PURPLE, display);
    insertShadowSquare(250, 200, 410, 220, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_bitmap(getBig(player1.character), (float) 430, 260, 0);
    insertShadowSquare(40, 200, 410, 490, LIGHT_PURPLE, DARK_PURPLE, display);
//
    insertShadowSquare(40, 200, 710, 35, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 742, 40, 0, "PLAYER 2");
//
    insertShadowSquare(40, 200, 710, 160, LIGHT_PURPLE, DARK_PURPLE, display);
    insertShadowSquare(250, 200, 710, 220, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_bitmap(getBig(player2.character), (float) 730, 260, 0);
    insertShadowSquare(40, 200, 710, 490, LIGHT_PURPLE, DARK_PURPLE, display);

    al_flip_display();
}


void drawGame() {
    //TELA DO JOGO
    al_clear_to_color(BLACK);
    moveBall();
    readCreatePlanetsBullets();

    for (int i = 0; i < player1.life; i++) {
        al_draw_bitmap(lifeHeart, 30 * i, 20, 0);
    }

    for (int i = 0; i < player2.life; i++) {
        al_draw_bitmap(lifeHeart, WINDOW_WIDTH - (30 * (i + 1)), 20, 0);
    }

    if (player1.life * player2.life == 0) {
        char* str = ((player1.life > 0) ? "JOGADOR 1 VENCEU" : "JOGADOR 2 VENCEU");
        al_draw_text(font90, WHITE, 185, 250, 0, str);
    } else {
        al_draw_filled_circle((float) player1.coordX, (float) player1.coordY, (float) player1.radius, BLACK);
        al_draw_bitmap((b.coordX > player1.coordX ? getSide(player1.character, 1) : getSide(player1.character, 0)), (float) player1.coordX - 36, player1.coordY - 36, 0);
        al_draw_filled_circle((float) player2.coordX, (float) player2.coordY, (float) player2.radius, BLACK);
        al_draw_bitmap((b.coordX > player2.coordX ? getSide(player2.character, 1) : getSide(player2.character, 0)), (float) player2.coordX - 36, player2.coordY - 36, 0);
    }

    al_draw_text(font45,  (gameRound ? LIGHT_BLUE : RED), 400, 25, 0, (gameRound ? "- VEZ DO JOGADOR 1 -" : "- VEZ DO JOGADOR 2 -"));
    al_flip_display();
}

void killNine() {
    printf(" - Killing APP....[%s]\n", getNow());
    al_destroy_bitmap(tittleWelcome);
    al_destroy_bitmap(tittleWorbit);
    al_destroy_bitmap(astro);
    al_destroy_bitmap(lifeHeart);
//    algif_destroy_animation(tuto);
    al_destroy_event_queue(timer_queue);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    exit(0);
}