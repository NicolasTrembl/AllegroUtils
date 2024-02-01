#include "collider_gameobject.h"
#include <allegro5/allegro_primitives.h>

void drawTriangle(point a, point b, point c, point offset){
    al_draw_line(a.x + offset.x, a.y + offset.y, b.x + offset.x, b.y + offset.y, al_map_rgb(1, 128, 10), 1.0);
    al_draw_line(a.x + offset.x, a.y + offset.y, c.x + offset.x, c.y + offset.y, al_map_rgb(1, 128, 10), 1.0);
    al_draw_line(c.x + offset.x, c.y + offset.y, b.x + offset.x, b.y + offset.y, al_map_rgb(1, 128, 10), 1.0);
}

void drawCollider(position pos, colliderParams* params) {
    for (int i = 0; i < params->trianglesCount; i++) {
        drawTriangle(
            params->triangles[i].a,
            params->triangles[i].b,
            params->triangles[i].c,
            pos.point
        );
    }
    
}

void deleteColliderParam(gameObject* gObject) {
    colliderParams* params = ((colliderParams *) gObject->params);
    free(params->triangles);
    free(params);
}

gameObject* newCollider(int* id, point triPoints[][3], int size) {
    gameObject* gObject = createEmptyGameObject(id, Collider);
    colliderParams* params = malloc(sizeof(colliderParams));

    Triangle* triangles = malloc(sizeof(Triangle) * size);
    
    for (int i = 0; i <= size; i++) {
        triangles[i] = (Triangle) {
            triPoints[i][0],
            triPoints[i][1],
            triPoints[i][2],
        };
    }
    

    *params = (colliderParams) {
        triangles,
        size
    };

    gObject->params = (void *) params;

    return gObject;
}

