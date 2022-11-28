
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <src/main.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <innerIncludes/headers/nossaLivraria.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <innerIncludes/headers/Cores.h>
#include <innerIncludes/headers/gameCore.h>
#include <outIncludes/headers/algif.h>
#include <innerIncludes/headers/sprites.h>


// ========== Window VARS ===========================================
int const WINDOW_WIDTH          = 1280;
int const WINDOW_HEIGHT         = 720;
// =================================================================

// ========== Frame VARS ===========================================
bool GAME_FREQUENCY_POLARITY    = false;
float const GAME_FREQUENCY      = 60; // Quantos ciclos de atualizacao acontecem no jogo
// ==================================================================

ALLEGRO_BITMAP *astro, *tittleWorbit, *tittleWelcome, *lifeHeart; // Imagens principais do jogo
ALLEGRO_EVENT_QUEUE *event_queue, *timer_queue; // Fila de eventos do usuario e FPS
ALLEGRO_FONT *font15, *font25, *font90, *font45; // Fontes do jogo
ALLEGRO_DISPLAY *display; // Display do jogo
ALGIF_ANIMATION *tuto, *tuto2; // gif do tutorial
ALLEGRO_TIMER *timer;

GAMEMODE GAMESTATE; //  Estado do q o usuario esta fazendo
bool orderRedraw = true;

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
        lifeHeart = al_load_bitmap("../src/assets/vida.png");
    }

    // Inicia o primeiro mapa
    activeMap = MAP1;

    const char *gif = "../src/assets/tutorial/giphy.gif";
    tuto = algif_load_animation(gif);
    const char *gif2 = "../src/assets/tutorial/giphy2.gif";
    tuto2 = algif_load_animation(gif2);

    // Inicia biblioteca de primitives
    al_init_primitives_addon();

    // Carrega as fontes do jogo
    if (al_init_font_addon() && al_init_ttf_addon()) {
        font15 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 15, 0);
        font25 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 25, 0);
        font45 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 45, 0);
        font90 = al_load_ttf_font("../src/assets/fonts/Bungee-Regular.ttf", 90, 0);
    }

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

// Lida com os eventos criados pelo usuario
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
                            // Inicia constante de newton
                            initGame();
                            GAMESTATE = TUTORIAL1;
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
                    if (!b.active && player1.life > 0 && player2.life > 0) {
                        setBulletTo(ev.mouse.x, ev.mouse.y);
                    }
                    break;
                }
                case TUTORIAL1: {
                    if (ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80) {
                        orderRedraw = true;
                        GAMESTATE = TUTORIAL2; // SKIPA PARTE DO TUTORIAL
                    }
                    break;
                }
                case TUTORIAL2: {
                    if (ev.mouse.x >= 30 && ev.mouse.x <= 230 && ev.mouse.y >= 30 && ev.mouse.y <= 80) {
                        orderRedraw = true;
                        GAMESTATE = PLAY; // SKIPA PARA O JOGO
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
                                player1.character = (SPRITE) (((int) player1.character + 1) > 5 ? 0 : player1.character + 1);
                                drawCharacterSelection(false);
                            } else if (ev.mouse.y >= 490 && ev.mouse.y <= 540) {
                                player1.character = (SPRITE) (((int) player1.character - 1) < 0 ? 5 : player1.character - 1);
                                drawCharacterSelection(false);
                            }
                        }
                        if (ev.mouse.x >= 710 && ev.mouse.x <= 910) {
                            if (ev.mouse.y >= 160 && ev.mouse.y <= 200) {
                                player2.character = (SPRITE) (((int) player2.character + 1) > 5 ? 0 : player2.character + 1);
                                drawCharacterSelection(false);
                            } else if (ev.mouse.y >= 490 && ev.mouse.y <= 540) {
                                player2.character = (SPRITE) (((int) player2.character - 1) < 0 ? 5 : player2.character - 1);
                                drawCharacterSelection(false);
                            }
                        }

                        break;
                    }
                    default: {
                        break;
                    }
                }
                case TRANSITION: {
                    // BOTÕES DA tela de transicao
                    // (float) WINDOW_WIDTH/2 - 150, (float) WINDOW_HEIGHT/2 + 130
                    if((ev.mouse.x >= WINDOW_WIDTH/2 - 150) && (ev.mouse.x <= WINDOW_WIDTH/2 + 150) && (ev.mouse.y >= WINDOW_HEIGHT/2 + 130) && (ev.mouse.y <= WINDOW_HEIGHT/2 + 210)) {
                        orderRedraw = true;
                        activeMap = (MAP) (((int) activeMap) + 1);
                        initGame();
                        GAMESTATE = PLAY;
                    }
                }

                break;
            }
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

// Renderiza qualquer tela
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
            case TUTORIAL1: {
                if (GAME_FREQUENCY_POLARITY) {
                    drawTutorial();
                    if (orderRedraw) {
                        printf(" - Drawing Tutorial....[%s]\n", getNow());
                        orderRedraw = false;
                    }
                }
                break;
            }
            case TUTORIAL2: {
            if (GAME_FREQUENCY_POLARITY) {
                drawTutorial2();
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
            case TRANSITION: {
                if (orderRedraw) {
                    drawTransition();
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

// Desenha as estrelas de fundo
void drawStars() {

    for (int i = 0; i < 90; ++i) {
        int randomX = getRandomInt(WINDOW_WIDTH, 0);
        int randomY = getRandomInt(WINDOW_HEIGHT, 0);
        int randomR = getRandomInt(4, 0);
        al_draw_filled_circle((float) randomX, (float) randomY, (float) randomR, WHITE);
    }
}

// Desenha o menu
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

void drawTransition() {
    al_clear_to_color(BLACK);
    al_draw_text(font90, WHITE, (float) WINDOW_WIDTH/2 - 450, WINDOW_HEIGHT/2 - 250, 0, player1.life<0 ? "Jogador 2 venceu" : "Jogador 1 venceu");
    insertShadowSquare(80, 300, (float) WINDOW_WIDTH/2 - 150, (float) WINDOW_HEIGHT/2 + 130, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, (float) WINDOW_WIDTH/2 - 60, (float) WINDOW_HEIGHT/2 + 160, 0, "Próximo");
    al_flip_display();
}

// Desenha os tutoriais
void drawTutorial() {
// TELA DE TUROTIAL
    al_clear_to_color(BLACK);

    al_draw_bitmap(algif_get_bitmap(tuto, al_get_time()), WINDOW_WIDTH/2 - 300, WINDOW_HEIGHT/2 - 169, 0);

    insertFilledSquare(50, 200, 40, 40, DARK_PURPLE, display);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);
    insertShadowSquare(50, 1000, (WINDOW_WIDTH / 2) - 500, 620, LIGHT_PURPLE, DARK_PURPLE, display);

    al_draw_text(font15, WHITE, (float) (WINDOW_WIDTH / 2.0) - 475, 627, 0, "  Antes de começarmos, você precisa de uma breve explicação sobre a gravidade.    (veja um exemplo a cima)");
    al_draw_text(font15, WHITE, (float) (WINDOW_WIDTH / 2.0) - 475, 648, 0, "'Quanto mais massa um objeto tem e mais perto ele está, maior sua força de atração sobre outro objeto'");
    al_draw_text(font25, WHITE, 90, 40, 0, "Next");

    al_flip_display();
}

void drawTutorial2() {
// TELA DE TUROTIAL
    al_clear_to_color(BLACK);

    al_draw_bitmap(algif_get_bitmap(tuto2, al_get_time()), WINDOW_WIDTH/2 - 106, WINDOW_HEIGHT/2 - 128, 0);

    insertFilledSquare(50, 200, 40, 40, DARK_PURPLE, display);
    insertFilledSquare(50, 200, 30, 30, LIGHT_PURPLE, display);
    insertShadowSquare(50, 1000, (WINDOW_WIDTH / 2) - 500, 620, LIGHT_PURPLE, DARK_PURPLE, display);

    al_draw_text(font15, WHITE, (float) (WINDOW_WIDTH / 2.0) - 475, 627, 0, "   ou seja, os maiores planetas irão atrair com mais força o projetil, assim dificultando a sua jogatina");
    al_draw_text(font15, WHITE, (float) (WINDOW_WIDTH / 2.0) - 475, 648, 0, "Está pronto para está batalha espacial? Quem acertar 4 vezes seu adversário primeiro ganha, boa sorte!!");
    al_draw_text(font25, WHITE, 90, 40, 0, "Skip");

    al_flip_display();
}

// Desenha as configurações
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
    al_draw_text(font25, WHITE, 410 + 45, 490 + 7, 0, "CHANGE");
//
    insertShadowSquare(40, 200, 710, 35, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 742, 40, 0, "PLAYER 2");
//
    insertShadowSquare(40, 200, 710, 160, LIGHT_PURPLE, DARK_PURPLE, display);
    insertShadowSquare(250, 200, 710, 220, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_bitmap(getBig(player2.character), (float) 730, 260, 0);
    insertShadowSquare(40, 200, 710, 490, LIGHT_PURPLE, DARK_PURPLE, display);
    al_draw_text(font25, WHITE, 710 + 45, 490 + 7, 0, "CHANGE");

    al_flip_display();
}

// Desenha o jogo
void drawGame() {
    //TELA DO JOGO
    al_clear_to_color(BLACK);
    moveBall();
    readCreatePlanetsBullets();

    if (player1.life * player2.life != 0) {
        for (int i = 1; i <= player1.life; i++) {
            al_draw_bitmap(lifeHeart, 30 * i, 20, 0);
        }

        for (int i = 1; i <= player2.life; i++) {
            al_draw_bitmap(lifeHeart, WINDOW_WIDTH - (30 * (i + 1)), 20, 0);
        }

        al_draw_filled_circle((float) player1.coordX, (float) player1.coordY, (float) player1.radius, BLACK);
        al_draw_bitmap((b.coordX > player1.coordX ? getSide(player1.character, 1) : getSide(player1.character, 0)), (float) player1.coordX - 36, player1.coordY - 36, 0);
        al_draw_filled_circle((float) player2.coordX, (float) player2.coordY, (float) player2.radius, BLACK);
        al_draw_bitmap((b.coordX > player2.coordX ? getSide(player2.character, 1) : getSide(player2.character, 0)), (float) player2.coordX - 36, player2.coordY - 36, 0);
    }

    if(player2.life > 0){
        if(gameRound){
            al_draw_text( font45, LIGHT_BLUE, 400, 25, 0, "- VEZ DO JOGADOR 1 -");
        }
    } else{
        finishGame();
        al_draw_text(font90, RED, 150, 60, 0, "JODADOR 2 VENCEU!");
    }

    if(player1.life > 0){
        if(!gameRound){
            al_draw_text( font45, RED, 400, 25, 0, "- VEZ DO JOGADOR 2 -");
        }
    } else{
        finishGame();
        al_draw_text(font90, LIGHT_BLUE, 150, 60, 0, "JODADOR 1 VENCEU!");
    }

    al_flip_display();
}

// Mata o progrma e libera a memoria
void killNine() {
    printf(" - Killing APP....[%s]\n", getNow());
    al_destroy_bitmap(tittleWelcome);
    al_destroy_bitmap(tittleWorbit);
    al_destroy_bitmap(astro);
    al_destroy_bitmap(lifeHeart);
    algif_destroy_animation(tuto);
    algif_destroy_animation(tuto2);
    al_destroy_event_queue(timer_queue);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    killSprites();

    exit(0);
}