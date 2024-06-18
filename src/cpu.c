#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"


void setup(struct CPU *cpu) {
    cpu->memory = (uint8_t *)malloc(4096 * sizeof(uint8_t));
    cpu->registers = (uint8_t *)malloc(16 * sizeof(uint8_t));
    cpu->stack = (uint8_t *)malloc(16 * sizeof(uint8_t)); 
    cpu->I = 0;
    cpu->DT = 0;
    cpu->ST = 0;
    cpu->SP = 0;
    cpu->PC = 0x200;
}

//loads an inputted program into memory starting from address Ox200
void load(struct CPU *cpu, uint8_t *program, int size) {
    for (int i = 0; i < size; i++) {
        cpu->memory[cpu->PC + i] = program[i];
    }
}







/*
    CHIP-8 instructions are divided into broad categories by the first “nibble”, or “half-byte”, which is the first hexadecimal number.
    Although every instruction will have a first nibble that tells you what kind of instruction it is, 
    the rest of the nibbles will have different meanings. 
    
    X: The second nibble. Used to look up one of the 16 registers (VX) from V0 through VF.
    Y: The third nibble. Also used to look up one of the 16 registers (VY) from V0 through VF.
    N: The fourth nibble. A 4-bit number.
    NN: The second byte (third and fourth nibbles). An 8-bit immediate number.
    NNN: The second, third and fourth nibbles. A 12-bit immediate memory addr

    Until the so called 'opcode' is checked, there is no way of telling how each nibble is meant to be interpreted.
    
*/


void cycle(struct CPU *cpu) {
    uint16_t cur_inst = cpu->memory[cpu->PC] << 8 | cpu->memory[cpu->PC + 1];

    uint8_t opcode=(cur_inst & 0xF000 >> 12);
    uint8_t reg_1=(cur_inst & 0x0F00 >> 8);
    uint8_t reg_2=(cur_inst & 0x00F0 >> 4);
    uint8_t num_4_bit=(cur_inst & 0x000F);
    uint8_t num_8_bit=(cur_inst & 0x00FF); 
    uint8_t im_address = (cur_inst & 0x0FFF);
}


int main() {
    struct CPU cpu;
    setup(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}
