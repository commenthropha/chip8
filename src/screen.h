#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

void intitialise_screen(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *screen);

#endif