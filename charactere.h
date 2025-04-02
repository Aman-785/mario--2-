/*
Contient la création du personnage (Mario) et les diverses caractéristiques qui le composent, pareil pour les monstres.
Va aussi gérer l'affichage des personnages et monstres. 
Attention : la map doit déjà être chargée avant de créer un personnage. 
*/

#ifndef DEF_CHARACTERE
#define DEF_CHARACTERE
    
    #include <SDL2/SDL.h>
    #include "file.h"

    #define WIDTH_MARIO 30 // Largeur des images Mario
    #define HEIGHT_MARIO 40 // Hauteur des images Mario
    #define NUMBER_IMAGE_MARIO 6 // Nombre d'images de Mario en tout

    typedef struct Personnage Personnage;
    struct Personnage {
        SDL_Texture** image; // Contient toutes les images nécessaires pour Mario (différentes directions et saut)
        SDL_Rect position; // Sa position à l'instant t
        int jump; // Si Mario saute lors de la montée du saut, jump = 1, sinon 0
        int jumptime; // Correspond à la durée depuis quand Mario fait un saut, à 70 on arrête
        int gravite; // Vaut 1 si Mario est dans les airs, 0 sinon
        int direction, dernieredirection; // Direction vers laquelle est dirigé Mario : 1 = droite, 2 = gauche, 0 = statique
        int temp; // Permet de faire varier les sprites de Mario dans le temps
        int win; // Vaut 1 si le personnage gagne, -1 s'il perd, 0 sinon
        int invisible; // Utilisé pour les goombas : vaut 1 quand il meurt, 0 s'il est en vie
        int lvl, lvlperdu;
    };

    // Déclarations des fonctions
    Personnage* creerMario(SDL_Renderer* renderer);
    void freePersonnage(Personnage* mario, Personnage** goomba, int nbGoomba);
    void chargerMario(Personnage* mario, SDL_Renderer* renderer);
    void gererDirection(SDL_Event* event, Personnage* mario);
    void gererSaut(Personnage* mario);
    void afficherMario(SDL_Renderer* renderer, Personnage* mario);
    void deplacerMario(Personnage* mario);


#endif