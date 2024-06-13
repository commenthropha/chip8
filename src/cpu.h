#include <stdint.h>

struct CPU {
    uint8_t *memory;
    uint8_t *registers;
    uint8_t *stack;
    int I; // Index Register
    int DT; // Delay Timer
    int ST; // Sound Timer
    int SP; // Stack Pointer
    int PC; // Program Counter
};