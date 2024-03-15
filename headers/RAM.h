#ifndef NES_EMULATOR_RAM_H
#define NES_EMULATOR_RAM_H

#include <vector>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>

class RAM {
public:
    RAM();
    ~RAM();


    uint8_t readByte(uint16_t address) const;
    void writeByte(uint16_t address, uint8_t value);
    void writeStackByte(uint16_t address, uint8_t value);
    void writeInstructionByte(uint16_t address, uint8_t value);
    void dump_memory_at_address(uint16_t address, std::ostream& outFile) const;
    void dump_memory() const;  // Declaration for the dump_memory function

private:
    std::vector<uint8_t> memory;
    // Add more private members as needed
};

#endif //NES_EMULATOR_RAM_H
