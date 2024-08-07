#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
//#include <SDL2/SDL.h>

/*
 * Initialises the CHIP-8 CPU
 */ 
void initialise_cpu(struct CPU *cpu) {
    cpu->memory = (uint8_t *)malloc(4096 * sizeof(uint8_t));
    cpu->registers = (uint8_t *)malloc(16 * sizeof(uint8_t));
    cpu->stack = (uint8_t *)malloc(16 * sizeof(uint8_t));
    // screen size is 64x32

    cpu ->screen = (uint8_t *)malloc(64 * 32 * sizeof(uint8_t)); 
    // load fontset into memory
    for (int i = 0; i < 80; i++) {
        cpu->memory[i] = FONTSET[i];
    }
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


void cycle(struct CPU *cpu) {

    // Fetch the current instruction
    uint16_t current_instruction = cpu->memory[cpu->PC] <<8 | cpu->memory[cpu->PC + 1];
    cpu->PC += 2;
    // opcode
    uint8_t opcode = (current_instruction & 0xF000) >> 12;

    // register address 1, X
    uint8_t reg_1=(current_instruction & 0x0F00) >> 8;


    // register address 2, Y
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
                    for (int i = 0; i < 64 * 32; i++) {
                        cpu->screen[i] = 0;
                    }
                    break;
                // 00EE return from subroutine
                case 0xEE:
                    cpu->SP--;
                    cpu->PC = cpu->stack[cpu->SP];
                    break;
            }
            break;
        
        // 1NNN jump to address NNN
        case 0x1:
            cpu->PC = im_address;
            break;
    
        // 2NNN call subroutine at NNN
        case 0x2:
            cpu->stack[cpu->SP] = cpu->PC;
            cpu->SP++;
            cpu->PC = im_address;
            break;
        
        // 3XNN skip next instruction iff X == NN
        case 0x3:
            if (cpu->registers[reg_1] == num_8_bit) {
                cpu->PC += 2;
            }
            break;
        
        // 4XNN skip next instruction iff X != NN
        case 0x4:
            if (cpu->registers[reg_1] != num_8_bit) {
                cpu->PC += 2;
            }
            break;
        
        // 5XY0 skip next instruction iff X == Y
        case 0x5:
            if (cpu->registers[reg_1] == cpu->registers[reg_2]) {
                cpu->PC += 2;
            }
            break;

        // 6XNN set register X to NN
        case 0x6:
            cpu->registers[reg_1] = num_8_bit;
            break;

        // 7XNN add NN to register X
        case 0x7:
            cpu->registers[reg_1] += num_8_bit;
            break;

        case 0x8:
            // 8XY0 Set X to Y
            switch (num_4_bit)
            {
            case 0x0:
                cpu->registers[reg_1] = cpu->registers[reg_2];

                break;

            // 8XY1 Set X to X | Y
            case 0x1:
                cpu->registers[reg_1] = cpu->registers[reg_1] | cpu->registers[reg_2];
                break;
            
            // 8XY2 Set X to X & Y
            case 0x2:
                cpu->registers[reg_1] = cpu->registers[reg_1] & cpu->registers[reg_2];
                break;

            // 8XY3 Set X to X ^ Y
            case 0x3:
                cpu->registers[reg_1] = cpu->registers[reg_1] ^ cpu->registers[reg_2];
                break;
            // 8XY4 Add Y to X, set VF to 1 if carry
            case 0x4:
                if (cpu->registers[reg_1] + cpu->registers[reg_2] > 255) {
                    cpu->registers[0xF] = 1;
                } else {
                    cpu->registers[0xF] = 0;
                }
                cpu->registers[reg_1] += cpu->registers[reg_2];
                break;
            // 8XY5 Subtract Y from X, set, VF to 0 if borrow
            case 0x5:
                if (cpu->registers[reg_1] > cpu->registers[reg_2]) {
                    cpu->registers[0xF] = 1;
                } else {
                    cpu->registers[0xF] = 0;
                }
                cpu->registers[reg_1] -= cpu->registers[reg_2];
                break;
            // 8XY6 Shift X right by 1, set VF to least significant bit of X
            case 0x6:
                cpu->registers[0xF] = cpu->registers[reg_1] & 0x1;
                cpu->registers[reg_1] >>= 1;
                break;
            // 8XY7 Set X to Y - X, set VF to 0 if borrow
            case 0x7:
                if (cpu->registers[reg_2] > cpu->registers[reg_1]) {
                    cpu->registers[0xF] = 1;
                } else {
                    cpu->registers[0xF] = 0;
                }
                cpu->registers[reg_1] = cpu->registers[reg_2] - cpu->registers[reg_1];
                break;
            // 8XYE Shift X left by 1, set VF to most significant bit of X
            case 0xE:
                cpu->registers[0xF] = cpu->registers[reg_1] >> 7;
                cpu->registers[reg_1] <<= 1;
                break;
    
            }
            
            break;

        // 9XY0 skip next instruction iff X != Y
        case 0x9:
            if (cpu->registers[reg_1] != cpu->registers[reg_2]) {
                cpu->PC += 2;
            }
            break;

        // ANNN Set I to NNN
        case 0xA:
            cpu->I = im_address;
            break;

        // BNNN Jump to address NNN + V0
        case 0xB:
            cpu->PC = im_address + cpu->registers[0];
            break;

        // CXNN Set X to random number & NN
        case 0xC:
            cpu->registers[reg_1] = rand() & num_8_bit;
            break;

        


        // DXYN draw sprite stored at I at X,Y onto buffer
        case 0xD:
            uint8_t x = cpu->registers[reg_1] & 63;
            uint8_t y = cpu->registers[reg_2] & 31;
            uint8_t height = num_4_bit;
            cpu->registers[0xF] = 0;
            for (int row=0; row<height; row++){
                uint8_t sprite_row = cpu->memory[cpu->I + row];
                for (int col=0; col<8; col++){
                    // get pixel from sprite byte with &, for each column
                    uint8_t pixel = sprite_row & (0x80 >> col); 
                    if (pixel){
                        if (cpu->screen[(y + row)*64+x + col]){
                            cpu->registers[0xF] = 1;
                        }
                        // create buffer to draw to screen
                        if (x + col < 64 && y + row < 32){
                        // pixels on screen are flipped if 1 present in sprite byte
                        cpu->screen[(y + row)*64+x + col] ^= 1;
                        }
                    }
                }
            }
            break;

        
    }
        

}

