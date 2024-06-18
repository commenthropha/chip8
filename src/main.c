#include "cpu.h"
#include "screen.h"

int main() {
    struct CPU cpu;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    intitialise_screen(window, renderer, texture);
    initialise_cpu(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}