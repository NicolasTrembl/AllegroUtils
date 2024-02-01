cmake_minimum_required(VERSION 3.5.0)
project(AllegroTest VERSION 0.1.0 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(
    AllegroTest main.c 
    Utils/2dlogics.h Utils/2dlogics.c
    Painter/painter.h Painter/painter.c
    GameObjects/gameObject.h GameObjects/gameObject.c
    GameObjects/TypeOfObjects/text_area_gameobject.h GameObjects/TypeOfObjects/text_area_gameobject.c
    GameObjects/TypeOfObjects/collider_gameobject.h GameObjects/TypeOfObjects/collider_gameobject.c
    GameObjects/TypeOfObjects/image_gameobject.h GameObjects/TypeOfObjects/image_gameobject.c
)
target_link_libraries(AllegroTest allegro.dll)
target_link_libraries(AllegroTest allegro_font.dll)
target_link_libraries(AllegroTest allegro_primitives.dll)
target_link_libraries(AllegroTest allegro_image.dll)
