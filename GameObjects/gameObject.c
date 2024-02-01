#include "gameObject.h"
#include "TypeOfObjects/text_area_gameobject.h"
#include "TypeOfObjects/collider_gameobject.h"
#include "TypeOfObjects/image_gameobject.h"
#include <stdlib.h>
#include <stdio.h>


int addGameObjectToGameObjectChildren(gameObject* gObject, gameObject* child) {
    int currentLength = gObject->childrenCount;
    if (currentLength > 0) {
        gObject->children = realloc(gObject->children, (currentLength + 1) * sizeof(gameObject *));
    } else {
        gObject->children = malloc(sizeof(gameObject *));
    }
    gObject->children[currentLength] = child;
    gObject->childrenCount++;

    if (gObject->type == Image) moveChildToCenter(*gObject, child->id);

    return gObject->childrenCount;
}


gameObject* createEmptyGameObject(int* id, enum ObjectTypeEnum type) {
    gameObject* gObject = malloc(sizeof(gameObject));

    *gObject = (gameObject) {
        ++(*id),
        type,
        NULL,
        (position) { 0, 0, DEFAULT_LAYER },
        0,
        NULL,
    };

    return gObject;
}



// ================ General methods ================ //

int addChildtoGameObject(gameObject* gObject, gameObject* child) {
    return addGameObjectToGameObjectChildren(gObject, child);
}

void deleteGameObject(gameObject* gObject){
    switch (gObject->type) {
        case Collider:
            deleteColliderParam(gObject);
        break;

        case TextArea:
            deleteTextAreaParam(gObject);
        break;
        
        default:
            break;
    }



    if (gObject->childrenCount != 0) {
        for (int i = 0; i < gObject->childrenCount; i++) {
            deleteGameObject(gObject->children[i]);
        }
        free(gObject->children);
    }
    free(gObject);
}

int deleteChildWithId(gameObject* gObject, int id) {
    if (gObject->id == id) {
        
        deleteGameObject(gObject);
        return 1;
    }


    for (int i = 0; i < gObject->childrenCount; i++) {
        if (deleteChildWithId(gObject->children[i], id)) {
            (gObject->childrenCount)--;
            printf("found");
            return 1;
        }
    }

    return 0;
    
}


position moveGameObject(gameObject* gObject, position offset) {
    gObject->pos.point.x += offset.point.x;
    gObject->pos.point.y += offset.point.y;

    return gObject->pos;
}
void putGameObjectAt(gameObject* gObject, position position) {
    gObject->pos.point.x = position.point.x;
    gObject->pos.point.y = position.point.y;
    
}


// ================ Type related methods ================ //


position drawGameObject(gameObject gObject, position offset) {
    switch (gObject.type) {
        case Node:
            // can't draw a node    
        break;
        
        case Collider:
            drawCollider(addPos(gObject.pos, offset), (colliderParams *) gObject.params);  
        break;
        
        case TextArea:
            drawTextArea(
                addPos(gObject.pos, offset),
                (textAreaParams *) gObject.params
            );
        break;
        
        case Image:
            drawImage(addPos(gObject.pos, offset), (imageParams *) gObject.params);   
        break;
        
        default:
            break;
    }
    
    return addPos(gObject.pos, offset);

    // if (gObject.children == NULL) return;

    // for (int i = 0; i < gObject.childrenCount; i++) {
    //     drawGameObject(*((gameObject *)gObject.children[i]), addPos(gObject.pos, offset));
    // }
}
