cmake_minimum_required(VERSION 3.5.0)
project(AllegroTest VERSION 0.1.0 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(
    AllegroTest main.c 
    Classes/gameObject.h Classes/gameObject.c
    Classes/gameObjects/text_area_gameobject.h Classes/gameObjects/text_area_gameobject.c
    Classes/gameObjects/collider_gameobject.h Classes/gameObjects/collider_gameobject.c
    Classes/gameObjects/image_gameobject.h Classes/gameObjects/image_gameobject.c
)
target_link_libraries(AllegroTest allegro.dll)
target_link_libraries(AllegroTest allegro_font.dll)
target_link_libraries(AllegroTest allegro_primitives.dll)
target_link_libraries(AllegroTest allegro_image.dll)
