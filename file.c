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
    int width, height;
    char niv0[20];
    FILE *file = fopen("niveau0.lvl", "r"); 
    if (file == NULL)
    {
        perror("erreur fichier");
        exit(1);
    }

    fgets(niv0, sizeof(niv0), file);

    fscanf(file, "%d %d", &width, &height);
    printf("%d %d",width,height);

    int **LoadedMap = malloc(width * sizeof(int));
    if (LoadedMap == NULL)
    {
        perror("erreur memoire");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < width; i++)
    {
        LoadedMap[i] = malloc(height * sizeof(int));
        if (LoadedMap[i] == NULL)
        {
            perror("erreur memoire 2");

            for (int j = 0; j < i; j++)
            {
                free(LoadedMap[j]);
            }
            free(LoadedMap);
            fclose(file);
            exit(1);
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            fscanf(file, "%d", &LoadedMap[i][j]);
            printf("%d",LoadedMap[i][j]);
        }
    }
}


