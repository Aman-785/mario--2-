#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "game.h"

// ligne de compilation gcc main.c file.c game.c event.c charactere.c -o mario -lSDL2main -lSDL2_image1 -lSDL2

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

void image1(SDL_Renderer *renderer) // Image du main
{
	SDL_Rect rect2 = {0, 0, 600, 600};
	SDL_Rect rect1 = {0, 0, 600, 600};

	SDL_RenderClear(renderer);
	SDL_Texture *texture = loadImage("img/menu.jpg", renderer);
	SDL_RenderCopy(renderer, texture, &rect1, &rect2);
	SDL_RenderPresent(renderer);
}
   //*
void image2(SDL_Renderer *renderer) // Image crédit
{
	SDL_Rect rect2 = {0, 0, 600, 600};
	SDL_Rect rect1 = {0, 0, 600, 600};

	SDL_RenderClear(renderer);
	SDL_Texture *texture = loadImage("img/credit.jpg", renderer);
	SDL_RenderCopy(renderer, texture, &rect1, &rect2);
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Mario", 700, 500, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	image1(renderer);

	SDL_Event event;
	int continuer = 1;

	while (SDL_PollEvent(&event) || continuer == 1) // Boucle infini
	{

		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Log("touche quit");
			continuer = 0;
			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)

			{
			case SDLK_1:
				SDL_Log("touche 1");
				jouer(renderer);
				
				break;

			case SDLK_3: // image crédit

				SDL_Log("touche 2");
				image2(renderer);

				break;
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}//kkkc 12
