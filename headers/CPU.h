#ifndef NES_EMULATOR_6502_H
#define NES_EMULATOR_6502_H

#include "RAM.h" // Include the header file for RAM
#include <bitset>
class CacheRegister
{
public:
    uint16_t location; // Memory location stored in the cache register
    uint8_t value;     // Value at the memory location stored in the cache register

    CacheRegister() : location(0), value(0) {} // Default constructor
};

class CPU
{
public:
CacheRegister cache[3];
    uint16_t PC;    // 16-bit Program Counter
    uint16_t SP;    // 8-bit Stack Pointer
    uint8_t A;      // 8-bit Accumulator
    uint8_t STATUS; // Status flag register. Status flags are in order (-)(C)(Z)(I)(D)(B)(O)(N)

    CPU();
    ~CPU();

    void executeInstruction(RAM &ram, uint8_t opcode, uint16_t address);
    void updateCache(uint16_t location, uint8_t value);
    uint8_t getCachedValue(uint16_t location);

    void ADC(RAM &ram, uint16_t address);
    void SBC(RAM &ram, uint16_t address);
    void LDA(RAM &ram, uint16_t address);
    void AND(RAM &ram, uint16_t address);
    void EOR(RAM &ram, uint16_t address);
    void JMP(RAM &ram, uint16_t address);
    void PSH(RAM &ram);
    void POP(RAM &ram);
    void process_instructions(RAM &ram, uint16_t start_address, uint16_t end_address);
    // Add more methods as needed
};

#endif // NES_EMULATOR_6502_H
