
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <src/main.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <deps/nossaLivraria.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <Cores.h>
#include <deps/gameCore.h>


// ========== Window VARS ===========================================
int const WINDOW_WIDTH          = 1280;
int const WINDOW_HEIGHT         = 720;
bool LIMIT_WALLS                  = false;
// =================================================================

// ========== Frame VARS ===========================================
bool GAME_FREQUENCY_POLARITY    = false;
float const GAME_FREQUENCY      = 60; // Quantos ciclos de atualizacao acontecem no jogo
float const MPS                 = GAME_FREQUENCY;  // Maximo de vezes o jogo é renderizado
float FPS                       = 0;   // Guarda quantas de vezes o jogo está sendo renderizado
bool allow                      = true;
bool SHOW_FPS                   = false;
long global_counter;
// ==================================================================


ALLEGRO_BITMAP *astro, *tittleWorbit, *tittleWelcome, *spritCatLeft, *spritCatRight, *spritMummyLeft, *spritMummyRight, *spritSullivanLeft,
*spritSullivanRight, *spritDemonLeft, *spritDemonRight;
ALLEGRO_EVENT_QUEUE *event_queue, *timer_queue;
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT *font25 , *font45;


int GAMESTATE = 0; // STATE INICIAL
bool orderRedraw = true;


int main() {

    // Inicia allegro
    al_init();

    // Inicia paleta de cores
    init_colors();

    // Carrega as imagens do jogo
    if (al_init_image_addon()) {
        astro = al_load_bitmap("../src/assets/astronauta.png");
        tittleWorbit = al_load_bitmap("../src/assets/worbit.png");
        tittleWelcome = al_load_bitmap("../src/assets/welcome.png");

        spritCatLeft = al_load_bitmap("../src/assets/characters/spritCatLeft.png");
        spritCatRight = al_load_bitmap("../src/assets/characters/spritCatRight.png");
        spritMummyLeft = al_load_bitmap("../src/assets/characters/spritMummyLeft.png");
        spritMummyRight = al_load_bitmap("../src/assets/characters/spritMummyRight.png");
        spritSullivanLeft = al_load_bitmap("../src/assets/characters/spritSullivanLeft.png");
        spritSullivanRight = al_load_bitmap("../src/assets/characters/spritSullivanRight.png");
        spritDemonLeft = al_load_bitmap("../src/assets/characters/spritDemonLeft.png");
        spritDemonRight = al_load_bitmap("../src/assets/characters/spritDemonRight.png");
    }

    // Inicia biblioteca de primitives
    al_init_primitives_addon();

    // Carrega as fontes do jogo
    if (al_init_font_addon() && al_init_ttf_addon()) {
        font25 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf",25,0 );
        font45 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf",45,0 );
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

    while (1) {
        ALLEGRO_EVENT ev;

        do {
            al_wait_for_event(event_queue, &ev); // ESPERANDO POR EVENTOS
            if (ev.type != ALLEGRO_EVENT_MOUSE_AXES) {
                eventHandler(ev);
                render(ev);
            }
        } while (!al_is_event_queue_empty(event_queue));

        while(al_is_event_queue_empty(event_queue)) {
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
                            killNine();
                        }
                    }
                    break;
                }
                case 1: {
                    // BOTÕES DA TELA PLAY
                    if (!b.active) {
                        setBulletTo(planetas[0].coordX, planetas[0].coordY - planetas[0].radius, ev.mouse.x, ev.mouse.y);
                    }

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
                default: {
                    break;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {
            if (ev.keyboard.keycode == 59) {
                orderRedraw = true;
                GAMESTATE = 0; // RETORNA A TELA DE MENU
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
            case 0: {
                if (orderRedraw) {
                    drawMenu();
                    orderRedraw = false;
                }
                break;
            }
            case 1: {
                drawGame();
                break;
            }
            case 2: {
                // TELA CONFIG
                if (orderRedraw) {
                    drawConfig();
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

void drawStars(){

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


    //SOMBRA OPÇÕES MENU
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 450, DARK_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 530, DARK_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-190, 610, DARK_PURPLE, display);

    //OPÇÕES MENU
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 440, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 520, LIGHT_PURPLE, display);
    insertFilledSquare(50, 400, (WINDOW_WIDTH/2)-200, 600, LIGHT_PURPLE, display);

    //FONTE MENU
    al_draw_text( font25, WHITE, (float) (WINDOW_WIDTH/2.0)-30, 455, 0, "Play");
    al_draw_text( font25, WHITE, (float) (WINDOW_WIDTH/2.0)-42, 535, 0, "Config");
    al_draw_text( font25, WHITE, (float) (WINDOW_WIDTH/2.0)-30, 615, 0, "Quit");

    //IMAGENS MENU
    al_draw_bitmap(astro, 870, 150, 0);
    al_draw_bitmap(tittleWorbit, (float) (WINDOW_WIDTH/2.0)-250, 80, 0);
    insertFilledSquare(17, 150, (WINDOW_WIDTH/2)-75, 30, BLACK, display);
    al_draw_bitmap(tittleWelcome, (float) (WINDOW_WIDTH/2.0)-75, 30, 0);

    printf(" - Drawing MENU....[%s]\n", getNow());
    al_flip_display();
}

void drawConfig() {
    // TELA DE CONFIGURAÇÕES
    al_clear_to_color(BLACK);

    drawStars();

    insertFilledSquare(50, 200, 40, 40, DARK_PURPLE, display);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);

    al_draw_text( font25, WHITE, 90, 40, 0, "Back");

    printf(" - Drawing SETTINGS....[%s]\n", getNow());
    al_flip_display();
}

void drawGame(){
    //TELA DO JOGO
    al_clear_to_color(BLACK);
    moveBall();
    readCreatePlanetsBullets();

    spritCatLeft = al_load_bitmap("../src/assets/characters/spritCatLeft.png");
    al_draw_bitmap(spritCatLeft, (float) (WINDOW_WIDTH/2.0), 400, 0);

    spritCatRight = al_load_bitmap("../src/assets/characters/spritCatRight.png");
    al_draw_bitmap(spritCatRight, (float) (WINDOW_WIDTH/2.0), 340, 0);



    spritMummyLeft = al_load_bitmap("../src/assets/characters/spritMummyLeft.png");
    al_draw_bitmap(spritMummyLeft, (float) (WINDOW_WIDTH/2.0 + 80), 400, 0);

    spritMummyRight = al_load_bitmap("../src/assets/characters/spritMummyRight.png");
    al_draw_bitmap(spritMummyRight, (float) (WINDOW_WIDTH/2.0 + 80), 340, 0);



    spritSullivanLeft = al_load_bitmap("../src/assets/characters/spritSullivanLeft.png");
    al_draw_bitmap(spritSullivanLeft, (float) (WINDOW_WIDTH/2.0 + 160), 400, 0);

    spritSullivanRight = al_load_bitmap("../src/assets/characters/spritSullivanRight.png");
    al_draw_bitmap(spritSullivanRight, (float) (WINDOW_WIDTH/2.0 + 160), 340, 0);



    spritDemonLeft = al_load_bitmap("../src/assets/characters/spritDemonLeft.png");
    al_draw_bitmap(spritDemonLeft, (float) (WINDOW_WIDTH/2.0 + 240), 400, 0);

    spritDemonRight = al_load_bitmap("../src/assets/characters/spritDemonRight.png");
    al_draw_bitmap(spritDemonRight, (float) (WINDOW_WIDTH/2.0 + 240), 340, 0);


    insertFilledSquare(12, 12, player1.coordX, player1.coordY, LIGHT_BLUE, display);
    insertFilledSquare(12, 12, player2.coordX, player2.coordY, RED, display);
    if(gameRound){
        al_draw_text( font45, LIGHT_BLUE, 400, 25, 0, "- VEZ DO JOGADOR 1 -");
    }else{
        al_draw_text( font45, RED, 400, 25, 0, "- VEZ DO JOGADOR 2 -");
    }
    al_flip_display();


    //printf(" - Drawing Play Screen....[%s]\n", getNow());
}

void killNine() {
    printf(" - Killing APP....[%s]\n", getNow());
    al_destroy_bitmap(tittleWelcome);
    al_destroy_bitmap(tittleWorbit);
    al_destroy_bitmap(astro);
    al_destroy_event_queue(timer_queue);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    exit(0);
}