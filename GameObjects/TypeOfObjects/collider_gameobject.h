#ifndef ColliderGameObject
#define ColliderGameObject

#include "../../Utils/2dlogics.h"
#include "../gameObject.h"

#include <allegro5/allegro5.h>

/*  Défini un triangle
    avec a, b, et c les 3 points
*/
typedef struct TriangleStruct {
    point a; 
    point b;
    point c;
} Triangle ;

/*  Paramètres d'un objet de type 'collider'
    @param triangles Les triangles qui le compose
    @param trianglesCount Le nombre de triangles
*/
typedef struct ColliderParameters {
    Triangle*   triangles;
    int         trianglesCount;
} colliderParams ;

/*  Affiche le collider
*/
void drawCollider(position pos, colliderParams* params);

/*  Supprime les paramètres du collider
*/
void deleteColliderParam(gameObject* gObject);

/*  Crée un nouveau collider selon les triangles indiqué
*/
gameObject* newCollider(int* id, point triPoints[][3], int size);

#endif