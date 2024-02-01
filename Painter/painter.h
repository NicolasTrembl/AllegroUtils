#ifndef PAINTER
#define PAINTER

#include "../GameObjects/gameObject.h"


typedef struct LayerAndObjects {
    int layer_z;
    gameObject** objects;
    int numbObjects;
} LnO;

typedef LnO* LnOS;

void drawAll(gameObject* root);


#endif 