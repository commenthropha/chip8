#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
#include <SDL2/SDL.h>

/*
 * Initialises the CHIP-8 CPU
 */ 
void initialise_cpu(struct CPU *cpu) {
    cpu->memory = (uint8_t *)malloc(4096 * sizeof(uint8_t));
    cpu->registers = (uint8_t *)malloc(16 * sizeof(uint8_t));
    cpu->stack = (uint8_t *)malloc(16 * sizeof(uint8_t)); 
    cpu->I = 0;
    cpu->DT = 0;
    cpu->ST = 0;
    cpu->SP = 0;
    cpu->PC = 0x200;
}

/*
 * Loads an inputted program into memory starting from address Ox200
 */ 
void load(struct CPU *cpu, uint8_t *program, int size) {
    for (int i = 0; i < size; i++) {
        cpu->memory[cpu->PC + i] = program[i];
    }
}


/*
    CHIP-8 instructions are divided into broad categories by the first “nibble”, or 
    “half-byte”,  which is the first hexadecimal number.
    
    Although every instruction will have a first nibble that tells you what kind of
    instruction it is, the rest of the nibbles will have different meanings. 
    
    X: The second nibble. Used to look up one of the 16 registers (VX) from V0 through VF.
    Y: The third nibble. Also used to look up one of the 16 registers (VY) from V0 through VF.
    N: The fourth nibble. A 4-bit number.
    NN: The second byte (third and fourth nibbles). An 8-bit immediate number.
    NNN: The second, third and fourth nibbles. A 12-bit immediate memory addr

    Until the so called 'opcode' is checked, there is no way of telling how each nibble
    is meant to be interpreted.
*/


void cycle(struct CPU *cpu, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    uint16_t opcode = cpu->memory[cpu->PC] << 8 | cpu->memory[cpu->PC + 1];
    uint8_t reg_1=(opcode & 0x0F00) >> 8;
    uint8_t reg_2=(opcode & 0x00F0) >> 4;
    uint8_t num_4_bit=(opcode & 0x000F);
    uint8_t num_8_bit=(opcode & 0x00FF); 
    uint8_t im_address = (opcode & 0x0FFF);


    // 00E0 - Clear display
    // 1NNN - Jump
    // 6XNN set register X to NN
    // 7XNN add NN to register X
    // ANNN set I to NNN
    // DXYN draw sprite at (VX, VY) with width 8 and height N

    switch (opcode){
        // Clear the screen
        case 0x00E0:
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            break;

}

