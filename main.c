#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Utils/2dlogics.h"
#include "Painter/painter.h"
#include "GameObjects/gameObject.h"
#include "GameObjects/TypeOfObjects/text_area_gameobject.h"
#include "GameObjects/TypeOfObjects/collider_gameobject.h"
#include "GameObjects/TypeOfObjects/image_gameobject.h"

const float FPS = 60;

// All the triangle's points 
point triPoints[4][3] = {
    { // Triangle 1
        (point) { 0, -31 }, 
        (point) { -28, -19 }, 
        (point) { 25, -20 } 
    },
    { // Triangle 2
        (point) { 25, -20 }, 
        (point) { 2, 29 }, 
        (point) { 26, 14 } 
    },
    { // Triangle 3
        (point) { -28, -19 }, 
        (point) { -25, 15 }, 
        (point) { 2, 29 } 
    },
    { // Triangle 4
        (point) { 25, -20 }, 
        (point) { -28, -19 }, 
        (point) { 2, 29 } 
    },
};

int main(){

    if(!al_init()) {
      fprintf(stderr, "Allegro ne marche pas!\n");
      return -1;
   }

    if (!al_install_keyboard()) fprintf(stderr, "Clavier marche pas");
    if (!al_init_primitives_addon()) fprintf(stderr, "Primitive marche pas");
    if (!al_init_font_addon()) fprintf(stderr, "Font marche pas");
    if (!al_init_image_addon()) fprintf(stderr, "Image marche pas");

    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    ALLEGRO_DISPLAY* disp = NULL;
    disp = al_create_display(640, 480);

    if(!disp) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_set_window_title(disp, "TEST");

    printf("Display ok");

    ALLEGRO_EVENT_QUEUE* queue = NULL; 
    queue = al_create_event_queue();
    if(!queue) {
        fprintf(stderr, "failed to create queue!\n");
        return -1;
    }


    ALLEGRO_FONT* font = NULL;
    font = al_create_builtin_font();
    if(!font) {
        fprintf(stderr, "failed to create font!\n");
        return -1;
    }

    ALLEGRO_MONITOR_INFO info = {0, 0, 0, 0};
    al_get_monitor_info(0, &info);

    ALLEGRO_TIMER* timer = NULL;
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;

    printf("\nAllegro is ok\n");
    
    /* Init id to zero */
    int id = 0;

    gameObject* root = createEmptyGameObject(&id, Node);

    gameObject* text1 = newTextArea(&id, "Test", font, al_map_rgb(225, 225, 225));
    gameObject* col1  = newCollider(&id, triPoints, 4);
    gameObject* img1  = newImage(&id, "..\\Assets\\images\\point.png");

    addChildtoGameObject(root, img1);

    addChildtoGameObject(img1, text1);
    addChildtoGameObject(img1, col1);

    // int width = info.x2 - info.x1;
    // int height = info.y2 - info.y1;

    int width = 640;
    int height = 480;

    position center = {
        width / 2,
        height / 2,
        DEFAULT_LAYER
    };

    putGameObjectAt(img1, center);

    position txtOffset = {
        15, 15, DEFAULT_LAYER
    };

    bool isLooping = true;

    bool redraw = true;

    printf("Setup ok\n");

    al_start_timer(timer);

    while (isLooping) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            printf("Key down\n");

            switch (event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    isLooping = false;
                break;
                default:
                break;
            }
        } else if (event.type == ALLEGRO_EVENT_TIMER) {

            position newPos = moveGameObject(img1, txtOffset);


            if (newPos.point.x >= width || newPos.point.x <= 0) txtOffset.point.x *= -1;
            if (newPos.point.y >= height || newPos.point.y <= 0) txtOffset.point.y *= -1;

            redraw = true;
        } else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if (redraw) {
            
            // draw part

            al_clear_to_color(al_map_rgb(0, 0, 0));            

            drawAll(root);

            redraw = false;
        }


    }

    al_destroy_timer(timer);
    timer = NULL;
    al_destroy_font(font);
    font = NULL;
    al_destroy_display(disp);
    disp = NULL;
    al_destroy_event_queue(queue);
    queue = NULL;
    al_shutdown_image_addon();
    deleteGameObject(root);
    printf("Cleaned\n");


    return 0;
}