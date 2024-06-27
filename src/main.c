#include "cpu.h"
#include "screen.h"


int main() {
    struct CPU cpu;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    int running = 1;

    // Initialize the CPU and screen
    initialise_cpu(&cpu);
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

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
