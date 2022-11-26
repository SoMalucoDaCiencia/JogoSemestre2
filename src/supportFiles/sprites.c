//
// Created by Arthur Andrade - home on 15/11/22.
//

#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <innerIncludes/headers/sprites.h>

ALLEGRO_BITMAP *spritCatLeft;               ALLEGRO_BITMAP *spritCatSelection;          ALLEGRO_BITMAP *spritCatRight;
ALLEGRO_BITMAP *spritMummyLeft;             ALLEGRO_BITMAP *spritMummySelection;        ALLEGRO_BITMAP *spritMummyRight;
ALLEGRO_BITMAP *spritSullivanLeft;          ALLEGRO_BITMAP *spritSullivanSelection;     ALLEGRO_BITMAP *spritSullivanRight;
ALLEGRO_BITMAP *spritDemonLeft;             ALLEGRO_BITMAP *spritDemonSelection;        ALLEGRO_BITMAP *spritDemonRight ;
ALLEGRO_BITMAP *spritWaterMonsterLeft;      ALLEGRO_BITMAP *spritWaterMonsterSelection; ALLEGRO_BITMAP *spritWaterMonsterRight;
ALLEGRO_BITMAP *spritZombieLeft;            ALLEGRO_BITMAP *spritZombieSelection;       ALLEGRO_BITMAP *spritZombieRight;

void loadSprites() {
    spritCatLeft               = al_load_bitmap("../src/assets/characters/spritCatLeft.png");
    spritCatRight              = al_load_bitmap("../src/assets/characters/spritCatRight.png");
    spritCatSelection          = al_load_bitmap("../src/assets/characters/spritCatSelection.png");
    spritMummyLeft             = al_load_bitmap("../src/assets/characters/spritMummyLeft.png");
    spritMummyRight            = al_load_bitmap("../src/assets/characters/spritMummyRight.png");
    spritMummySelection        = al_load_bitmap("../src/assets/characters/spritMummySelection.png");
    spritSullivanLeft          = al_load_bitmap("../src/assets/characters/spritSullivanLeft.png");
    spritSullivanRight         = al_load_bitmap("../src/assets/characters/spritSullivanRight.png");
    spritSullivanSelection     = al_load_bitmap("../src/assets/characters/spritSullivanSelection.png");
    spritDemonLeft             = al_load_bitmap("../src/assets/characters/spritDemonLeft.png");
    spritDemonRight            = al_load_bitmap("../src/assets/characters/spritDemonRight.png");
    spritDemonSelection        = al_load_bitmap("../src/assets/characters/spritDemonSelection.png");
    spritWaterMonsterLeft      = al_load_bitmap("../src/assets/characters/spritWaterMonsterLeft.png");
    spritWaterMonsterRight     = al_load_bitmap("../src/assets/characters/spritWaterMonsterRight.png");
    spritWaterMonsterSelection = al_load_bitmap("../src/assets/characters/spritWaterMonsterSelection.png");
    spritZombieLeft            = al_load_bitmap("../src/assets/characters/spritZombieLeft.png");
    spritZombieRight           = al_load_bitmap("../src/assets/characters/spritZombieRight.png");
    spritZombieSelection       = al_load_bitmap("../src/assets/characters/spritZombieSelection.png");
}

ALLEGRO_BITMAP* getSide(SPRITE im, bool right) {
    switch (im) {
        case CAT      : return right ? spritCatRight : spritCatLeft;
        case MUMMY    : return right ? spritMummyRight : spritMummyLeft;
        case SULLIVAN : return right ? spritSullivanRight : spritSullivanLeft;
        case DEMON    : return right ? spritDemonRight : spritDemonLeft;
        case WATER    : return right ? spritWaterMonsterRight : spritWaterMonsterLeft;
        case ZOMBIE   : return right ? spritZombieRight : spritZombieLeft;
    }
}

ALLEGRO_BITMAP* getBig(SPRITE im) {
    switch (im) {
        case CAT      : return spritCatSelection         ;
        case MUMMY    : return spritMummySelection       ;
        case SULLIVAN : return spritSullivanSelection    ;
        case DEMON    : return spritDemonSelection       ;
        case WATER    : return spritWaterMonsterSelection;
        case ZOMBIE   : return spritZombieSelection      ;
    }
}