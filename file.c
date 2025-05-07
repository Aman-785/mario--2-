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
  

for (int i = 0; i < NbSprites; i++) {
    if (sprites[i].sprite != NULL) {
        SDL_DestroyTexture(sprites[i].sprite);
        sprites[i].sprite = NULL; 
    }
}


if (map->LoadedMap != NULL) {
    for (int i = 0; i < map->height; i++) {
        if (map->LoadedMap[i] != NULL) {
            free(map->LoadedMap[i]);
        }
    }
    free(map->LoadedMap);
    map->LoadedMap = NULL;
}
    


}

void texture(Sprites *sprites, SDL_Renderer *renderer)
{

    SDL_Texture *texture[11];

    texture[0] = loadImage("img/sky.png", renderer);
    texture[1] = loadImage("img/solpng", renderer);
    texture[2] = loadImage("img/block.png", renderer);
    texture[3] = loadImage("img/boite.png", renderer);
    texture[4] = loadImage("img/tuyau1.png", renderer);
    texture[5] = loadImage("img/tuyau2.png", renderer);
    texture[6] = loadImage("img/tuyau3.png", renderer);
    texture[7] = loadImage("img/tuyau4.png", renderer);
    texture[8] = loadImage("img/fin1.png", renderer);
    texture[9] = loadImage("img/fin2.png", renderer);
    texture[10] = loadImage("img/goomba1.png", renderer);

    for (int i = 0; i < 11; i++)
    {
        sprites[i].sprite = texture[i];
    }

    sprites[0].traverser = 0;
    sprites[1].traverser = 1;
    sprites[2].traverser = 1;
    sprites[3].traverser = 1;
    sprites[4].traverser = 1;
    sprites[5].traverser = 1;
    sprites[6].traverser = 1;
    sprites[7].traverser = 1;
    sprites[8].traverser = 0;
    sprites[9].traverser = 0;
    sprites[10].traverser = 1;
}

void lire(Map *map)
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
    SDL_Log("%d %d", width, height);

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
            SDL_Log("%d", LoadedMap[i][j]);
        }
    }
}