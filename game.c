#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"

int jouer(SDL_Renderer *renderer)
{

    // charger image et personnage.

    int continuer = 1; // a utiliser pour savoir si on continue la boucle du jeu ou si on arrête.
    SDL_Event events;
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    while (continuer)
    { // coeur du jeu ici, les actions seront repété pour faire le déplacement des différentes images, ...
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    // a vous de compléter, au fur et à mesure, les deux fonctions en dessous pour bien faire le nettoyage.
    // LibererMap(map, sprites);
    // freePersonnage(mario, goomba, nbGoomba);

    return continuer;
}