#include "RAM.h"
#include <iostream>

RAM::RAM() {
    // Constructor implementation
    memory.resize(2 * 1024, 0);
}

RAM::~RAM() {
    // Destructor implementation
    memory.clear();
}

// Additional method to read a byte at a specific address
uint8_t RAM::readByte(uint16_t address) const {
    if (address < memory.size()) {
        // Check if the address is within the valid range
            return memory[address];
        
    } else {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to read from invalid memory address." << std::endl;
        return 0;  // Return a default value (you may choose a different approach)
    }
}
void RAM::writeInstructionByte(uint16_t address, uint8_t value) {
    if (address < memory.size()) {
        if (address < 256) {
            memory[address] = value;
            std::cerr << "Wrote to instruction space memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        } else {
            std::cerr << "Error: Attempted to write instruction byte outside the Instruction space." << std::endl;
        }
    } else {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
}

void RAM::writeStackByte(uint16_t address, uint8_t value) {
    if (address < memory.size()) {
        if (address < 512 && address> 256) {
            memory[address] = value;
            std::cerr << "Wrote to instruction space memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        } else {
            std::cerr << "Error: Attempted to write instruction byte outside the Instruction space." << std::endl;
        }
    } else {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
}


void RAM::writeByte(uint16_t address, uint8_t value) {
    if (address < memory.size()) {
        // Check if the address is within the valid range
        if (address < 512) {
            std::cerr << "Error: Attempted to write to reserved instruction or stack space." << std::endl;
        } else {
            memory[address] = value;
            std::cerr << "Wrote to memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        }
    } else {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
}

void RAM::dump_memory_at_address(uint16_t address) const {
    // Every 16 bytes, create a line of dump output in hexadecimal

        // Print starting address of bytes in this line of output
        std::cout << "Address 0x" << std::hex << std::setw(4) << address << ": ";

        // Print sixteen bytes in memory from starting address
        for (int i = 0; i < 16; i++) {
            if (address + i < memory.size()) {
                uint8_t byte = readByte(address + i);
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
            } else {
                // Print spaces for empty spaces in the last line
                std::cout << "   ";
            }
        }

        // Print ASCII representation for each byte
        std::cout << "| ";
        for (int i = 0; i < 16; i++) {
            if (address + i  < memory.size()) {
                uint8_t byte = readByte(address + i);
                // Display printable characters, otherwise show a dot
                char printableChar = (byte >= 32 && byte <= 126) ? static_cast<char>(byte) : '.';
                std::cout << printableChar;
            } else {
                // Print spaces for empty spaces in the last line
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    
}

void RAM::dump_memory() const {
    const int bytesPerLine = 16;

    // Iterate over each byte in memory and print in groups of 16 bytes per line
    for (uint16_t address = 0; address < memory.size(); address += bytesPerLine) {
        dump_memory_at_address(address);
    }
}