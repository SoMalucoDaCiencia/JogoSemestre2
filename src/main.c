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
#include <deps/gameCore.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <Cores.h>

int const WINDOW_WIDTH          = 1280;
int const WINDOW_HEIGHT         = 720;
bool LIMIT_WALLS                  = false;

bool GAME_FREQUENCY_POLARITY    = false;
float const GAME_FREQUENCY      = 60; // Quantos ciclos de atualizacao acontecem no jogo
float const MPS                 = 60; // Maximo de vezes o jogo é renderizado
float FPS;                            // Guarda quantas de vezes o jogo esta sendo renderizado
bool allow                      = true;
bool SHOW_FPS                   = false;

double NEWTON;

int ballRadius                  = 1;
int ballSpeedX                  = -2;
int ballSpeedY                  = 0;
int ballXCoord                  = 950;
int ballYCoord                  = 55;


ALLEGRO_BITMAP *astro, *tittleWorbit, *tittleWelcome;
ALLEGRO_FONT *font;


void drawStars(){
    srand(time(NULL));
    int randomX = rand() % WINDOW_WIDTH;
    int randomY = rand() % WINDOW_HEIGHT;
    int randomR = rand() % 1 + 4;

    for (int i = 0; i < 90; ++i) {
        randomX = rand() % WINDOW_WIDTH;
        randomY = rand() % WINDOW_HEIGHT;
        randomR = rand() % 1 + 4;
        al_draw_filled_circle(randomX, randomY, randomR, WHITE);
    }
}

void drawMenu(ALLEGRO_DISPLAY* display) {
    // TELA DO MENU
    al_clear_to_color(BLACK);

    //DESENHA ESTRELAS
    drawStars();

    //SOMBRA OPÇÕES MENU
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 450, DARK_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 530, DARK_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 610, DARK_PURPLE, display);

    //OPÇÕES MENU
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 520, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 600, LIGHT_PURPLE, display);

    //FONTE MENU
    al_draw_text( font, WHITE, (WINDOW_WIDTH/2)-30, 455, 0, "Play");
    al_draw_text( font, WHITE, (WINDOW_WIDTH/2)-42, 535, 0, "Config");
    al_draw_text( font, WHITE, (WINDOW_WIDTH/2)-30, 615, 0, "Quit");

    //IMAGENS MENU
    al_draw_bitmap(astro, 870, 150, 0);
    al_draw_bitmap(tittleWorbit, (float)(WINDOW_WIDTH/2)-250, 80, 0);
    insertFilledSquare(17, 150, (WINDOW_WIDTH/2)-75, 30, BLACK, display);
    al_draw_bitmap(tittleWelcome, (float)(WINDOW_WIDTH/2)-75, 30, 0);

    printf(" - Drawing MENU....[%s]\n", getNow());
    al_flip_display();
}

void drawConfig(ALLEGRO_DISPLAY* display) {
    // TELA DE CONFIGURAÇÕES
    al_clear_to_color(BLACK);

    drawStars();

    insertFilledSquare(50, 200, 40, 40, DARK_PURPLE, display);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);

    al_draw_text( font, WHITE, 90, 40, 0, "Back");

    printf(" - Drawing SETTINGS....[%s]\n", getNow());
    al_flip_display();
}

int main() {

    // Inicia allegro
    al_init();

    // Carrega as imagens do jogo
    if (al_init_image_addon()) {
        astro = al_load_bitmap("../src/assets/astronauta.png");
        tittleWorbit = al_load_bitmap("../src/assets/worbit.png");
        tittleWelcome = al_load_bitmap("../src/assets/welcome.png");
    }

    // Inicia biblioteca de primitives
    al_init_primitives_addon();

    // Carrega as fontes do jogo
    if (al_init_font_addon() && al_init_ttf_addon()) {
        font = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf",25,0 );
    }


    // Inicia constante de newton
    NEWTON = 6.6743 * pow(10, -11);

    // Inicia pilha de eventos do allegro
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // Inicia event listener do mouse
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia event listener do teclado
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Inicia display
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_clear_to_color(BLACK);

    // Inicia loops por GAME_FREQUENCY
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / GAME_FREQUENCY);
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
                                al_destroy_bitmap(tittleWorbit);
                                al_destroy_bitmap(tittleWelcome);
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
                GAME_FREQUENCY_POLARITY = !GAME_FREQUENCY_POLARITY; // POLARIDADE DO GAME_FREQUENCY
                switch (GAMESTATE) {
                    case 0: {
                        if (orderRedraw) {
                            drawMenu(display);
                            orderRedraw = false;
                        }
                        break;
                    }
                    case 1: {
                        // TELA PLAY
                        if(allow){
                            int started = getUnix();
                            al_flip_display();
                            float millis = (float)(getUnix() - started);
                            if(millis <= MPS/1000){
                                FPS = MPS;
                                allow = false;
                            } else{
                                FPS = 1000/millis;
                            }

                        } else{
                            FPS -= 1;
                            allow = true;
                        }
                        al_clear_to_color(WHITE);
                        al_draw_filled_circle(560, 120, 100, BLACK);

                        printf("%f\n", FPS);
                        printf("\n%d\n", GAME_FREQUENCY_POLARITY);
                        moveBall();

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
                al_destroy_bitmap(tittleWorbit);
                al_destroy_bitmap(tittleWelcome);
                killNine(timer, display, event_queue);
                // ^^ SALVA SEU COMPUTADOR DE EXPLODIR
                break;
            }
        }
    }
}