#include "cpu.h"
#include "screen.h"

int main() {
    struct CPU cpu;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    initialise_screen(&window, &renderer, &texture);
    draw_test(window, renderer, texture);
    initialise_cpu(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}