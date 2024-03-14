#include "Emulator.h"
#include "CPU.h"
#include "RAM.h"

int main()
{
    // Instantiate the classes
    CPU cpu;
    RAM ram;

    // 1. Load program into memory
    std::ifstream inputFile("instructions.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    uint16_t address = 0x0000;


    while (std::getline(inputFile, line)) {
    std::cout << line << std::endl;

    std::istringstream iss(line);

    // Keep reading 5 characters (bits) until the end of the line
    for (int j = 0; j < 3; ++j) {
        uint8_t byteValue = 0;

        for (int i = 0; i < 8; ++i) {
            char bitChar;
            if (!(iss >> bitChar)) {
                std::cerr << "Error: Insufficient bits in the line." << std::endl;
                return 1;
            }

            // Check if the character is a binary value (0 or 1)
            if (bitChar != '0' && bitChar != '1') {
                std::cerr << "Error: Non-binary character found in the line." << std::endl;
                return 1;
            }

            // Set the corresponding bit in the byteValue
            byteValue |= (bitChar == '1') << (7 - i);
        }

        // Write the byte to RAM
        ram.writeInstructionByte(address, byteValue);

        // Increment the address for the next byte
        ++address;
    }
}

    std::ifstream inputDataFile("data.txt");

    // Check if the file is open
    if (!inputDataFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read the file line by line
    line;
    address = 0x0200;

    while (std::getline(inputDataFile, line))
    {
        std::cout << line << std::endl;

        std::istringstream iss(line);
        uint8_t byteValue;

        // Keep reading bytes until the end of the line
        while (iss >> std::hex >> byteValue)
        {
            // Write the byte to RAM
            ram.writeByte(address, byteValue);

            // Increment the address for the next byte
            ++address;
        }
    }

    ram.dump_memory_at_address(0x0200);
    ram.dump_memory();

    cpu.process_instructions(ram, 0x0000, 0x004);

    // 2. CPU starts reading/executing instructions from program space

    // 3. Program Terminates when instructions run out

    return 0;
}
