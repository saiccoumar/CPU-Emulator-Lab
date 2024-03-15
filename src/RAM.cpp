#include "RAM.h"

RAM::RAM()
{
    // Constructor implementation
    memory.resize(2 * 1024, 0);
    dump_memory();
}

RAM::~RAM()
{
    // Destructor implementation
    memory.clear();
}

// Additional method to read a byte at a specific address
uint8_t RAM::readByte(uint16_t address) const
{
    if (address < memory.size())
    {
        // Check if the address is within the valid range
        return memory[address];
    }
    else
    {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to read from invalid memory address." << std::endl;
        return 0xFF; // Return a default value 
    }
}
void RAM::writeInstructionByte(uint16_t address, uint8_t value)
{
    if (address < memory.size())
    {
        if (address < 256)
        {
            memory[address] = value;
            std::cerr << "Wrote to instruction space memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        }
        else
        {
            std::cerr << "Error: Attempted to write instruction byte outside the Instruction space." << std::endl;
        }
    }
    else
    {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
    dump_memory();
}

void RAM::writeStackByte(uint16_t address, uint8_t value)
{
    if (address < memory.size())
    {
        if (address < 512 && address >= 256)
        {
            memory[address] = value;
            std::cerr << "Wrote to stack space memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        }
        else
        {
            std::cerr << "Error: Attempted to write instruction byte outside the Instruction space." << std::endl;
        }
    }
    else
    {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
    dump_memory();
}

void RAM::writeByte(uint16_t address, uint8_t value)
{
    if (address < memory.size())
    {
        // Check if the address is within the valid range
        if (address < 512)
        {
            std::cerr << "Error: Attempted to write to reserved instruction or stack space." << std::endl;
        }
        else
        {
            memory[address] = value;
            std::cerr << "Wrote to memory address."
                      << " Address: 0x" << std::hex << address
                      << ", Memory Size: 0x" << memory.size() << std::endl;
        }
    }
    else
    {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to write to invalid memory address."
                  << " Address: 0x" << std::hex << address
                  << ", Memory Size: 0x" << memory.size() << std::endl;
    }
    dump_memory();
}

void RAM::dump_memory_at_address(uint16_t address, std::ostream& out) const {
    // Every 16 bytes, create a line of dump output in hexadecimal
    // Print starting address of bytes in this line of output
    out << "Address 0x" << std::hex << std::setw(4) << address << ": ";

    // Print sixteen bytes in memory from starting address
    for (int i = 0; i < 64; i++) {
        if (address + i < memory.size()) {
            uint8_t byte = readByte(address + i);
            out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        } else {
            // Print spaces for empty spaces in the last line
            out << "   ";
        }
    }

    // Print ASCII representation for each byte
    out << "| ";
    for (int i = 0; i < 64; i++) {
        if (address + i < memory.size()) {
            uint8_t byte = readByte(address + i);
            // Display printable characters, otherwise show a dot
            char printableChar = (byte >= 32 && byte <= 126) ? static_cast<char>(byte) : '.';
            out << printableChar;
        } else {
            // Print spaces for empty spaces in the last line
            out << " ";
        }
    }

    out << std::endl;
}


void RAM::dump_memory() const {
    const int bytesPerLine = 16;
    
    // Open file for writing
    std::ofstream outFile("RAM.txt");
    
    // Check if file opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // Iterate over each byte in memory and print in groups of 16 bytes per line
    for (uint16_t address = 0; address < memory.size(); address += 4 * bytesPerLine) {
        dump_memory_at_address(address, outFile);
    }
    
    // Close the file stream
    outFile.close();
}