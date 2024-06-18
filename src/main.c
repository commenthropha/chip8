#include "cpu.h"
#include "screen.h"

int main() {
    struct CPU cpu;
    SDL_Window *chip8_screen = NULL;
    SDL_Renderer *chip8_renderer = NULL;
    SDL_Texture *chip8_texture = NULL;

    intitialise_screen(chip8_renderer, chip8_screen, chip8_texture);
    initialise_cpu(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}