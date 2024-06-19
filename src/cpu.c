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

    // Fetch the current instruction
    uint16_t current_instruction = cpu->memory[cpu->PC]| cpu->memory[cpu->PC + 2];

    // opcode
    uint8_t opcode = (current_instruction & 0xF000) >> 12;

    // register address 1
    uint8_t reg_1=(current_instruction & 0x0F00) >> 8;


    // register address 2
    uint8_t reg_2=(current_instruction & 0x00F0) >> 4;

    // 4 bit number
    uint8_t num_4_bit=(current_instruction & 0x000F);

    // 8 bit immediate number
    uint8_t num_8_bit=(current_instruction & 0x00FF); 

    // 12 bit immediate address
    uint16_t im_address = (current_instruction & 0x0FFF);


    // 6XNN set register X to NN
    // 7XNN add NN to register X
    // ANNN set I to NNN
    // DXYN draw sprite at (VX, VY) with width 8 and height N

    switch (opcode) {
        case 0x0:
            switch (num_8_bit) {
                // 00E0 clear the screen
                case 0xE0:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    break;
            }
            break;
        
        // 1NNN jump to address NNN
        case 0x1:
            cpu->PC = im_address;
            break;
    
        // 6XNN set register X to NN
        case 0x6:
            cpu->registers[reg_1] = num_8_bit;
            break;

        // 7XNN add NN to register X
        case 0x7:
            cpu->registers[reg_1] += num_8_bit;
            break;
            break;
    }
        

}

