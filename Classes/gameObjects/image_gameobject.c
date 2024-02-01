#include "image_gameobject.h"
#include "../gameObject.h"
#include <allegro5/allegro_image.h>


void drawImage(position pos, imageParams* params) {
    if (params->image != NULL) {
        al_draw_bitmap(params->image, (float) pos.point.x, (float) pos.point.y, 0);
    }
}


void deleteImageParam(gameObject* gObject) {
    imageParams* params = ((imageParams *) gObject->params);
    free(params);
}

gameObject* newImage(int* id, char* path) {
    gameObject* gObject = createEmptyGameObject(id, Image);
    imageParams* params = malloc(sizeof(imageParams));

    ALLEGRO_BITMAP* img = al_load_bitmap(path);

    *params = (imageParams) {
        img,
        (point) {al_get_bitmap_width(img), al_get_bitmap_height(img)}
    };

    gObject->params = (void *) params;

    return gObject;
}

void moveChildToCenter(gameObject gObject, int childId) {
    for (int i = 0; i < gObject.childrenCount; i++) {
        if ((((gameObject**) gObject.children)[i])->id != childId) continue;
        moveGameObject(
            gObject.children[i], 
            (position) { 
                (point) {((imageParams *) gObject.params)->size.x / 2, ((imageParams *) gObject.params)->size.y / 2} , 
                gObject.pos.layer
            }
        );
        return;
    }
    
}


