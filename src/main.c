#include "cpu.h"
#include "screen.h"

int main() {
    struct CPU cpu;

    setup(&cpu);

    free(cpu.memory);
    free(cpu.registers);
    free(cpu.stack);

    return 0;
}