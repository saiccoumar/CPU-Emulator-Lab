#ifndef NES_EMULATOR_6502_H
#define NES_EMULATOR_6502_H

#include "RAM.h"  // Include the header file for RAM
#include <bitset>
class CPU {
public:
    CPU();
    ~CPU();

    void executeInstruction(RAM& ram, uint8_t opcode, uint16_t address);
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
    void process_instructions(RAM& ram, uint16_t start_address, uint16_t end_address);
    // Add more methods as needed
};

#endif //NES_EMULATOR_6502_H
