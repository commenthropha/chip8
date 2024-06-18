#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 600

int intitialise_screen(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *screen);

#endif