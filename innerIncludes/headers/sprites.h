//
// Created by Arthur Andrade - home on 12/10/22.
//

#ifndef JOGOSEMESTRE2_OUR_IMAGES_H
#define JOGOSEMESTRE2_OUR_IMAGES_H

#include <allegro5/bitmap.h>

    typedef enum {
        CAT,
        MUMMY,
        SULLIVAN,
        DEMON,
        WATER,
        ZOMBIE
    } SPRITE;

extern ALLEGRO_BITMAP *spritCatLeft, *spritCatRight, *spritCatSelection, *spritMummyLeft, *spritMummyRight, *spritMummySelection, *spritSullivanLeft,
        *spritSullivanRight, *spritSullivanSelection, *spritDemonLeft, *spritDemonRight, *spritDemonSelection, *spritWaterMonsterLeft, *spritWaterMonsterRight,
        *spritWaterMonsterSelection, *spritZombieLeft, *spritZombieRight, *spritZombieSelection;

    void loadSprites();

    void killSprites();

    ALLEGRO_COLOR getSpriteColor(SPRITE im);

    ALLEGRO_BITMAP* getSide(SPRITE im, bool right);

    ALLEGRO_BITMAP* getBig(SPRITE im);


#endif //JOGOSEMESTRE2_OUR_IMAGES_H
