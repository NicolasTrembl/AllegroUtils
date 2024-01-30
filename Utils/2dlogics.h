#ifndef LOGICFOR2D
#define LOGICFOR2D

#define SHOWDEBUG 1

//  ================= LAYER =================  //


/*  Les layers sont des 'tranches' virtuelle du jeu 
    @param z_index La profondeur de la tranche
    @param d_name Son nom utile pour débugguer
*/
typedef struct layerStruct { 
    int                 z_index;
    char*               d_name;
} layer;

/* Layer par défaut */
#define DEFAULT_LAYER   (layer) { 128, "DEFAULT" }

/* Layer d'UI */
#define UI_LAYER        (layer) { 512, "UI" }


//  =============== POSITIONS ===============  //

/*  Un point en 2 dimension
*/
typedef struct Point2D {
    int x, y;
} point;


/*  Représente la position dans le jeu
    @param x Sa coordonnée en X
    @param y Sa coordonnée en Y
    @param layer Sa layer
*/
typedef struct Position2D {
    point               point;
    layer               layer;
} position ;

#endif