#include "text_area_gameobject.h"

void drawTextArea(position pos, textAreaParams* params) {

    al_draw_text(
        params->font,
        params->color,
        pos.point.x,
        pos.point.y,
        0,
        params->text
    );
}

void deleteTextAreaParam(gameObject* gObject){
    free(gObject->params);

}

gameObject* newTextArea(int* id, char* text, ALLEGRO_FONT* font, ALLEGRO_COLOR color) {
    gameObject* gObject = createEmptyGameObject(id, TextArea);
    textAreaParams* params = malloc(sizeof(textAreaParams));
    
    *params = (textAreaParams) {
        text, font, color
    };

    gObject->params = (void *) params;

    return gObject;
}

