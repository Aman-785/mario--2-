#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

// ligne de compilation gcc main.c file.c game.c event.c charactere.c -o mario -lSDL2main -lSDL2_image -lSDL2

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

void image(SDL_Renderer *renderer)
{
	SDL_Rect rect2 = {0, 0, 600, 600};
	SDL_Rect rect1 = {0, 0, 600, 600};

	SDL_RenderClear(renderer);
	SDL_Texture *texture = loadImage("img/menu.jpg", renderer);
	SDL_RenderCopy(renderer, texture, &rect1, &rect2);
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Mario", 700, 500, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	image(renderer);
	SDL_Delay(5000);
	SDL_Quit();
}
