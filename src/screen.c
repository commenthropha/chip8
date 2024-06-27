#include "screen.h"
#include "cpu.h"
/*
 * Initialises the CHIP-8 screen using SDL2
 */
void initialise_screen(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "\e[0;31mFailed to initialise the SDL2 library\e[0m: %s", SDL_GetError());
        exit(1);
    }

    (*window) = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
    if(!(*window))
    {
        fprintf(stderr, "\e[0;31mFailed to create window\e[0m: %s", SDL_GetError());
        exit(1);
    }

    (*renderer) = SDL_CreateRenderer((*window), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!(*renderer))
    {
        fprintf(stderr, "\e[0;31mFailed to create renderer\e[0m: %s", SDL_GetError());
        exit(1);
    }

	*texture = SDL_CreateTexture((*renderer), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(!(*texture)) {
        fprintf(stderr, "\e[0;31mFailed to create texture\e[0m: %s", SDL_GetError());
        exit(1);
    }    

	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
	SDL_RenderClear(*renderer);	
    SDL_RenderPresent(*renderer);
}

void draw_test(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 30;
    rect.h = 30;
    
    SDL_SetRenderDrawColor(renderer, 25, 205, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderDrawPoint(renderer, 10, 10);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void update_screen(struct CPU *cpu, SDL_Renderer *renderer, SDL_Texture *texture) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the screen
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (cpu->screen[y * SCREEN_WIDTH + x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            } 
            
        }
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}