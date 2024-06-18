#include "cpu.h"
#include "screen.h"

int main() {
    struct CPU cpu;
    SDL_Window *chip8_screen;
    SDL_Renderer *chip8_renderer;
    SDL_Texture *chip8_texture;

    setup(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}