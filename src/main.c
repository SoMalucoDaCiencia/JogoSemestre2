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
#define background "background.bmp"

int main() {

    al_init();
//    al_init_image_addon();
//    al_init_primitives_addon();

    al_create_display(1280,720);

    //ALLEGRO_BITMAP *image = al_load_bitmap(background);
    //al_draw_bitmap(image, 0, 0, 0);
    //al_destroy_bitmap(image);
    while(1==1){
    }
}