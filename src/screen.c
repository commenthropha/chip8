#include "screen.h"

int intitialise_screen(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Failed to initialize the SDL2 library", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
    if(!window)
    {
        fprintf(stderr, "Failed to create window", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
    {
        fprintf(stderr, "Failed to create renderer", SDL_GetError());
        return -1;
    }

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(!texture) {
        fprintf(stderr, "Failed to create texture", SDL_GetError());
        return -1;  
    }

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);	
    SDL_RenderPresent(renderer);
}