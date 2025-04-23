#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "file.h"

/*permet de charger une image dans une SDL_Texture avec l'option SDL_TEXTUREACCESS_TARGET
pour pouvoir modifier la texture après. */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *tmp = NULL, *texture = NULL;
    surface = IMG_Load(path);
    if (NULL == surface)
    {
        fprintf(stderr, "Erreur IMG_Load : %s", SDL_GetError());
        return NULL;
    }
    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if (NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    if (texture == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    SDL_SetRenderTarget(renderer, texture);           /* La cible de rendu est maintenant texture. */
    SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_NONE); /* gère la transparence du fond des images*/
    SDL_RenderCopy(renderer, tmp, NULL, NULL);        /* On copie tmp sur texture */
    SDL_DestroyTexture(tmp);                          // nettoyage
    SDL_FreeSurface(surface);                         // nettoyage
    SDL_SetRenderTarget(renderer, NULL);              /* La cible de rendu est de nouveau le renderer. */
    return texture;
}

void LibererMap(Map *map, Sprites *sprites)
{
}
void *allouer(int taille)
{ // allocation mémoire

    taille = 10;
    int *allouer = (int *)malloc(taille * sizeof(int));

    if (allouer == NULL)
    {
        perror("erreur allocation");
        free(allouer);
    }

}



void lire(){ // ouvrire le fichier niveau0.lvl
    struct Map t;
    int width, height , a;
    char niv0[5];
    FILE *file = fopen("niveau0.lvl", "r");
    if (file == NULL)
    {
        perror("erreur fichier");
    }

    fgets(niv0, 5, file);
    printf("%s", niv0);

    fscanf(file, "%d %d ", &width, &height);
    printf("%d %d", width, height);

    while(fscanf(file, "%d" , &a)){
     
         
        
    }


    fclose(file);
}
