#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"


void texture(Sprites sprites[], SDL_Renderer *renderer);

void lire(Map *map);

int jouer(SDL_Renderer *renderer)
{

    // charger image et personnage.
    Map map = {0};
    Sprites sprites[NbSprites] = {0};
    texture(sprites, renderer);
    lire(&map);
    Personnage *mario = creerMario(renderer);
    if (!mario) {
        fprintf(stderr, "Erreur lors de la création de Mario.\n");
        return 0;
    }
    int continuer = 1; // a utiliser pour savoir si on continue la boucle du jeu ou si on arrête.
    SDL_Event events;
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    while (continuer)
    { // coeur du jeu ici, les actions seront repété pour faire le déplacement des différentes images, ...
        SDL_RenderClear(renderer);
    
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                default:
                    gererDirection(&events, mario);
                    break;
            }
        }
    
        deplacerMario(mario); 
        gererSaut(mario);     
        afficherMario(renderer, mario);
    
        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    // a vous de compléter, au fur et à mesure, les deux fonctions en dessous pour bien faire le nettoyage.
    LibererMap(&map, sprites);
    freePersonnage(mario, NULL, 0);

    return continuer;
}//5