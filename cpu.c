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
}


int main() {
    struct CPU cpu;
    setup(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}
