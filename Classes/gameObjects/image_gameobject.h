#ifndef ImageGameObject
#define ImageGameObject

#include "../../Utils/2dlogics.h"
#include "../gameObject.h"

#include <allegro5/allegro5.h>

/*  Les paramètres des objet 'image'
    @param image L'image en question
    @param size La taille de l'image
*/
typedef struct ImageParameters {
    ALLEGRO_BITMAP* image;
    point           size;
} imageParams ;

/*  Affiche l'image
    @note Si l'image n'est pas trouvé rien n'est affiché
*/
void drawImage(position pos, imageParams* params);

/*  Supprime le paramètres de l'image
*/
void deleteImageParam(gameObject* gObject);

/*  Crée un nouvelle image avec l'image a l'adresse 'path'
*/
gameObject* newImage(int* id, char* path);

/*  Mets l'image au centre de l'objet indiqué   // FIXME
*/
void moveChildToCenter(gameObject gObject, int childId);

#endif