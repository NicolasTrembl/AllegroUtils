#include "painter.h"
#include "../GameObjects/gameObject.h"
#include <allegro5/allegro5.h>
#include <stdio.h>


void invPtr(LnO* a, LnO* b) { 
    LnO temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
int partition(LnOS* set, int low, int high) { 
  
    int pivot = (*set)[low].layer_z; 
    int i = low; 
    int j = high; 
  
    while (i < j) { 
  
        while ((*set)[i].layer_z <= pivot && i <= high - 1) { 
            i++; 
        } 
  
        while ((*set)[j].layer_z > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            invPtr(&(*set)[i], &(*set)[j]); 
        } 
    } 
    invPtr(&(*set)[low], &(*set)[j]); 
    return j; 
} 
  
void sortSet(LnOS* set, int low, int high) { 
    if (low < high) {   
        int partitionIndex = partition(set, low, high); 
  
        sortSet(set, low, partitionIndex - 1); 
        sortSet(set, partitionIndex + 1, high); 
    } 
} 

void addToSet(LnOS* set, int* size, gameObject* gObject) {
    for (int i = 0; i < gObject->childrenCount; i++) {
        addToSet(set, size, gObject->children[i]);
    }
    printf("Doing %d\n", gObject->id);

    int searchFor = gObject->pos.layer.z_index;

    for (int i = 0; i < *size; i++) {
        if ((*set)[i].layer_z != searchFor) continue;
        (*set)[i].numbObjects++;
        (*set)[i].objects = realloc((*set)[i].objects, sizeof(gameObject *) * (*set)[i].numbObjects);
        (*set)[i].objects[(*set)[i].numbObjects-1] = gObject;
        return;
    }
    (*size)++;
    int a = *size;
    printf("%d\n", *size);
    *set = realloc(*set, sizeof(LnO) * *size);
    printf("new set %d\n", set);

    gameObject** object = malloc(sizeof(gameObject *));
    object[0] = gObject;
    *(set[*size-1]) = (LnO) {
        searchFor,
        object,
        1
    };
}

void deleteSet(LnOS* set, int size) {
    for (int i = 0; i < size; i++){
        printf("%d\n", (*set)[i].numbObjects);
        if ((*set)[i].numbObjects == 0) continue;
        free((*set)[i].objects);
    }

    free(*set);
    *set = NULL;
}

LnOS buildSetAndDraw(gameObject* root) {
    int size = 0;
    LnOS set = malloc(0);

    addToSet(&set, &size, root);

    sortSet(&set, 0, size);

    position allPos[size] = {DEFAULTPOSITION};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < set[i].numbObjects; j++) {
            // drawGameObject(*(set[i].objects[j]), DEFAULTPOSITION);
        }
        
    }
    

    deleteSet(&set, size);


}

void drawAll(gameObject* root) {
    buildSetAndDraw(root);


    al_flip_display();


}