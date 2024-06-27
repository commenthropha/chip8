#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "screen.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to ROM>\n", argv[0]);
        return 1;
    }

    // Open the ROM file
    FILE *rom = fopen(argv[1], "rb");
    if (!rom) {
        fprintf(stderr, "Failed to open ROM: %s\n", argv[1]);
        return 1;
    }

    // Identify the ROM size
    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    // Allocate memory for the ROM
    uint8_t *buffer = (uint8_t *)malloc(rom_size);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for ROM\n");
        fclose(rom);
        return 1;
    }

    // Read the ROM into the buffer
    fread(buffer, rom_size, 1, rom);
    fclose(rom);

    struct CPU cpu;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    int running = 1;

    // Initialise the CPU and load the ROM
    initialise_cpu(&cpu);
    load(&cpu, buffer, rom_size);
    // Free the ROM buffer after loading it into CPU memory
    free(buffer);

    // Initialise the screen
    initialise_screen(&window, &renderer, &texture);

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        draw_test(window, renderer, texture);
    }

    // Clean up
    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);
    free(cpu.screen);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}