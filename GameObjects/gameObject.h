#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "../Utils/2dlogics.h"


/*  Type de sous-objets */
enum ObjectTypeEnum {
    Node,           // <- objet vide, par defaut
    Collider,       // <- objet de collision
    TextArea,       // <- objet "panneau", affiche du texte
    Image,          // <- objet "image", affiche une image
    AnimatedImage,  // <- objet animé, dirigé par un arbre d'état // TODO
    
} ;

/*  Représente un objet / éléments du jeu
    @param id L'identifiant unique
    @param type Le type de l'objet
    @param params Ses paramètres, dépend de son type
    @param pos Sa position, relative a l'objet supérieur ( ou a l'écran ) // TODO 
    @param children La liste de ses 'enfants'
*/
typedef struct gameObjectStruct {
    int                 id;
    enum ObjectTypeEnum type;
    void*               params;
    position            pos;
    int                 childrenCount;
    struct gameObjectStruct** children;
} gameObject ;

/* Crée un objet vide selon le type
*/
gameObject* createEmptyGameObject(int* id, enum ObjectTypeEnum type);


/*  Supprime l'object et ses enfants
    @note Pour supprimer juste un enfant, utilisez deleteChildWithId
*/
void    deleteGameObject(gameObject* gObject);

/*  Ajoute un enfant a l'objet
    @return Le nombre total d'enfants
*/
int     addChildtoGameObject(gameObject* gObject, gameObject* child);

/*  Vérifie si l'objet contient un enfant avec l'identifiant indiqué
    et le supprime si c'est le cas
    @return 1 si un enfant a été trouvé et supprimé, 0 sinon
*/
int     deleteChildWithId(gameObject* gObject, int id);


/*  Déplace l'objet de l'offset indiqué
    @return La nouvelle position
*/
position moveGameObject(gameObject* gObject, position offset);

/*  Déplace l'objet a la nouvelle position
    @return La nouvelle position
*/
void    putGameObjectAt(gameObject* gObject, position position);


/*  Affiche l'objet
    @note Si ses enfant peuvent être affiché, ils le sont 
*/
position    drawGameObject(gameObject gObject, position offset);


#endif