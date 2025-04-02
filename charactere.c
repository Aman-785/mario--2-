#include <stdlib.h>
#include <stdio.h>
#include "charactere.h"

Personnage* creerMario(SDL_Renderer* renderer) {
    Personnage* mario = malloc(sizeof(Personnage));
    if (!mario) {
        fprintf(stderr, "Erreur d'allocation mémoire pour Mario.\n");
        return NULL;
    }



    
    mario->image = malloc(NUMBER_IMAGE_MARIO * sizeof(SDL_Texture*));
    if (!mario->image) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les images de Mario.\n");
        free(mario);
        return NULL;
    }

    mario->image[0] = loadImage("img/Mario1.png", renderer); 
    mario->image[1] = loadImage("img/Mario2.png", renderer); 
    mario->image[2] = loadImage("img/Mario3.png", renderer); 
    mario->image[3] = loadImage("img/Mario4.png", renderer); 
    mario->image[4] = loadImage("img/Mario5.png", renderer); 
    mario->image[5] = loadImage("img/Mario6.png", renderer);
    mario->position.x = 50;
    mario->position.y = 450;
    mario->position.w = WIDTH_MARIO;
    mario->position.h = HEIGHT_MARIO;

    mario->jump = 0;
    mario->jumptime = 0;
    mario->gravite = 0;
    mario->direction = 0;
    mario->dernieredirection = 3;
    mario->temp = 0;
    mario->win = 0;
    mario->invisible = 0;
    mario->lvl = 0;
    mario->lvlperdu = 0;

    return mario;
}

void freePersonnage(Personnage* mario, Personnage** goomba, int nbGoomba) {
    if (mario) {
        if (mario->image) {
            for (int i = 0; i < NUMBER_IMAGE_MARIO; i++) {
                if (mario->image[i]) {
                    SDL_DestroyTexture(mario->image[i]);
                }
            }
            free(mario->image);
        }
        free(mario);
    }

    if (goomba) {
        for (int i = 0; i < nbGoomba; i++) {
            if (goomba[i]) {
                if (goomba[i]->image) {
                    for (int j = 0; j < NUMBER_IMAGE_MARIO; j++) {
                        if (goomba[i]->image[j]) {
                            SDL_DestroyTexture(goomba[i]->image[j]);
                        }
                    }
                    free(goomba[i]->image);
                }
                free(goomba[i]);
            }
        }
        free(goomba);
    }
}

void afficherMario(SDL_Renderer* renderer, Personnage* mario) {
  if (!mario || !mario->image || !mario->image[0]) {
      fprintf(stderr, "Erreur : Mario ou son image n'est pas initialisé.\n");
      return;
  }

  int numImg = 0; 

 
  if (mario->jump == 1) {
      if (mario->dernieredirection == 1) {
          numImg = 2; 
      } else if (mario->dernieredirection == 2) {
          numImg = 5;
      }
  } else {
      mario->temp++;
      if (mario->temp >= 10) {
          mario->temp = 0;
      }

      if (mario->direction == 1) {
          numImg = 1;
      } else if (mario->direction == 2) {
          numImg = 4;
      } else if (mario->direction == 0) {
          if (mario->dernieredirection == 1) {
              numImg = 0; 
          } else if (mario->dernieredirection == 2) {
              numImg = 3;
          }
      }
  }

  SDL_RenderCopy(renderer, mario->image[numImg], NULL, &mario->position);
}

void gererDirection(SDL_Event* event, Personnage* mario) {
  if (!mario) return;

  switch (event->type) {
      case SDL_KEYDOWN:
          switch (event->key.keysym.sym) {
              case SDLK_RIGHT:
                  mario->direction = 1; 
                  mario->dernieredirection = 1;
                  break;
              case SDLK_LEFT:
                  mario->direction = 2; 
                  mario->dernieredirection = 2;
                  break;
              case SDLK_UP:
                  if (mario->jump == 0) { 
                      mario->jump = 1;
                      mario->jumptime = 0;
                  }
                  break;
          }
          break;

      case SDL_KEYUP:
          if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT) {
              mario->direction = 0; 
          }
          break;
  }
}

void deplacerMario(Personnage* mario) {
  if (!mario) return;

  const int vitesse = 5; 

  if (mario->direction == 1) {
      mario->position.x += vitesse;
  } else if (mario->direction == 2) { 
      mario->position.x -= vitesse;
  }
}


void gererSaut(Personnage* mario) {
  if (!mario || mario->jump == 0) return;
  const int hauteurMax = 45;
  const int vitesseSaut = 5;

  static int positionInitialeY = 0;

  if (mario->jumptime == 0) {
    positionInitialeY = mario->position.y; 
  }

  if (mario->jumptime < hauteurMax) {
    mario->position.y -= vitesseSaut;
    mario->jumptime++;
  } else {
    mario->position.y += vitesseSaut;
    if (mario->position.y >= positionInitialeY) {
      mario->position.y = positionInitialeY; 
      mario->jump = 0;
    }
  }
}

