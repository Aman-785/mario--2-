#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"


void texture(Sprites sprites[], SDL_Renderer *renderer);

void lire(Map *map);

int jouer(SDL_Renderer *renderer)
{
    Map map = {0};
    Sprites sprites[NbSprites] = {0};
    texture(sprites, renderer);
    lire(&map);

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
    LibererMap(&map, sprites);

    return continuer;
}