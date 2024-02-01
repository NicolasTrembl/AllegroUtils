#ifndef TextAreaGameObject
#define TextAreaGameObject

#include "../../Utils/2dlogics.h"
#include "../gameObject.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

/*  Les paramètres des objet 'panneau'
    @param text Le texte affiché
    @param font La police
    @prama color La couleur du texte
*/
typedef struct TextAreaParameters {
    char* text;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;
} textAreaParams ;

/*  Affiche le texte
*/
void drawTextArea(position pos, textAreaParams* params);

/*  Supprime les paramètres
*/
void deleteTextAreaParam(gameObject* gObject);

/*  Crée un nouvel objet texte
*/
gameObject* newTextArea(int* id, char* text, ALLEGRO_FONT* font, ALLEGRO_COLOR color);

#endif