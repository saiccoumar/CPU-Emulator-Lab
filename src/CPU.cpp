#include "CPU.h"
#include <iostream>
class CacheRegister
{
public:
    uint16_t location; // Memory location stored in the cache register
    uint8_t value;     // Value at the memory location stored in the cache register

    CacheRegister() : location(0), value(0) {} // Default constructor
};
CacheRegister cache[3];
uint16_t PC;    // 16-bit Program Counter
uint16_t SP;    // 8-bit Stack Pointer
uint8_t A;      // 8-bit Accumulator
uint8_t STATUS; // Status flag register. Status flags are in order (-)(C)(Z)(I)(D)(B)(O)(N)
// The first bit is unused.
// C is the carry flag which is set if the last operation caused an overflow or underflow
// Z is the zero flag which is set if the result of the last operation was 0
// I is interrupt disable. The processor will not respond to I/O interrupts when this is set
// D is decimal for BCD arithmetic during addition/subtraction
// B is break and set when BRK has been executed
// O is for signed overflow
// N is negative which is set if the result of last operation had bit 7 set to one

CPU::CPU()
{
    PC = 0;
    SP = 0;
    A = 0;
    STATUS = 0b00000000;
    // Constructor implementation
    // std::cout << "CPU initialized." << std::endl;
}

CPU::~CPU()
{
    // Destructor implementation
    // std::cout << "CPU destructed." << std::endl;
}

void CPU::process_instructions(RAM &ram, uint16_t start_address, uint16_t end_address)
{
    PC = start_address;

    // Fetch-Execute Cycle
    while (PC < end_address)
    {
        // Fetch 16 bytes from RAM
        uint16_t instruction_byte;

        instruction_byte = ram.readByte(PC);
        // Decode and execute the instruction
        executeInstruction(ram, instruction_byte);
        // Move to the next 8-byte block
        PC += 2;
    }
}

void CPU::updateCache(uint16_t location, uint8_t value)
{
    // Check if the location already exists in the cache
    for (int i = 0; i < 3; i++)
    {
        if (cache[i].location == location)
        {
            // If the location exists, update its value
            cache[i].value = value;
            return;
        }
    }

    // If the location doesn't exist in the cache, find the least recently used cache register to replace
    // Cache policy is to replace the location that's closest because it's the cheapest
    int mostRecentCacheRegister = 0;
    for (int i = 0; i < 3; i++)
    {
        if (cache[i].location < cache[mostRecentCacheRegister].location)
        {
            mostRecentCacheRegister = i;
        }
    }

    // Update the least recently used cache register with the new location and value
    cache[mostRecentCacheRegister].location = location;
    cache[mostRecentCacheRegister].value = value;
}

uint8_t CPU::getCachedValue(uint16_t location)
{
    // Check if the location exists in the cache
    for (int i = 0; i < 3; i++)
    {
        if (cache[i].location == location)
        {
            // If the location exists, return its cached value
            return cache[i].value;
        }
    }

    // If the location doesn't exist in the cache, return 0 (cache miss)
    return -1;
}

void CPU::executeInstruction(RAM &ram, uint16_t instruction_byte)
{
    std::cout << "Executing CPU instruction: < ";

    // Print the instruction in binary
    std::bitset<16> binaryInstruction(instruction_byte);
    std::cout << binaryInstruction;

    // Extract the first four bits
    uint8_t opcode = (instruction_byte >> 12) & 0x0F;

    // Execute instructions based on the opcode
    switch (opcode)
    {
    case 0b0000: // Handle instructions with opcode starting with '0000'
        ADC(ram, instruction_byte);
        break;
    case 0b0001: // Handle instructions with opcode starting with '0001'
        SBC(ram, instruction_byte);
        break;
    case 0b0010: // Handle instructions with opcode starting with '0010'
        LDA(ram, instruction_byte);
        break;
    case 0b0011: // Handle instructions with opcode starting with '0011'
        AND(ram, instruction_byte);
        break;
    case 0b0100: // Handle instructions with opcode starting with '0100'
        EOR(ram, instruction_byte);
        break;
    case 0b0101: // Handle instructions with opcode starting with '0101'
        JMP(ram, instruction_byte);
        break;
    case 0b0110: // Handle instructions with opcode starting with '0110'
        PSH(ram);
        break;
    case 0b0111: // Handle instructions with opcode starting with '0111'
        POP(ram);
        break;
    default:
        std::cerr << "NOP Unsupported opcode: " << std::bitset<3>(opcode) << std::endl;
        // Handle unsupported opcode
        break;
    }

    std::cout << " >";
    std::cout << std::endl;
}

void CPU::ADC(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    uint8_t value = getCachedValue(address);
    if (value == -1)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // Adding the value to the accumulator
    // Note: This addition might cause overflow, and the carry flag should be considered.
    uint8_t result = A + value + (STATUS & 0b01000000); // Adding the carry flag

    // Setting the zero flag if the result is zero
    if (result == 0)
    {
        STATUS |= 0b00100000; // Set Z flag
    }
    else
    {
        STATUS &= ~0b00100000; // Clear Z flag
    }

    // Setting the carry flag if there's overflow
    if (result > 255)
    {
        STATUS |= 0b01000000; // Set C flag
    }
    else
    {
        STATUS &= ~0b01000000; // Clear C flag
    }

    // Setting the overflow flag if the result overflows a signed 8-bit value
    if ((A ^ value) & 0b10000000 && (A ^ result) & 0b10000000)
    {
        STATUS |= 0b00000010; // Set O flag
    }
    else
    {
        STATUS &= ~0b00000010; // Clear O flag
    }

    // Setting the negative flag if the result's most significant bit is set
    if (result & 0b10000000)
    {
        STATUS |= 0b00000001; // Set N flag
    }
    else
    {
        STATUS &= ~0b00000001; // Clear N flag
    }

    // Writing the result back to memory at the same address
    ram.writeByte(address, result & 0xFF);
    updateCache(address, result & 0xFF);
    // Displaying the operation
    std::cout << "ADC instruction executed. Result stored at memory address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::SBC(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    uint8_t value = getCachedValue(address);
    if (value == -1)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }
    
    // Subtracting the value from the accumulator, considering the carry flag
    uint8_t result = value - A - ((STATUS & 0b01000000) ? 0 : 1); // Subtracting the carry flag if it's clear

    // Setting the zero flag if the result is zero
    if (result == 0)
    {
        STATUS |= 0b00100000; // Set Z flag
    }
    else
    {
        STATUS &= ~0b00100000; // Clear Z flag
    }

    // Setting the carry flag if there's no borrow (result >= 0)
    if (result < 256)
    {
        STATUS |= 0b01000000; // Set C flag
    }
    else
    {
        STATUS &= ~0b01000000; // Clear C flag
    }

    // Setting the overflow flag if the result overflows a signed 8-bit value
    if ((A ^ value) & 0b10000000 && (A ^ result) & 0b10000000)
    {
        STATUS |= 0b00000010; // Set O flag
    }
    else
    {
        STATUS &= ~0b00000010; // Clear O flag
    }

    // Setting the negative flag if the result's most significant bit is set
    if (result & 0b10000000)
    {
        STATUS |= 0b00000001; // Set N flag
    }
    else
    {
        STATUS &= ~0b00000001; // Clear N flag
    }

    // Writing the result back to memory at the same address
    ram.writeByte(address, result & 0xFF);
    updateCache(address, result & 0xFF);

    // Displaying the operation
    std::cout << "SBC instruction executed. Result stored at memory address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::LDA(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    uint8_t value = getCachedValue(address);
    if (value == -1)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // Loading the value into the accumulator (A register)
    A = value;
    
    updateCache(address, value);

    // Displaying the operation
    std::cout << "LDA instruction executed. Value loaded into accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::AND(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    uint8_t value = getCachedValue(address);
    if (value == -1)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }
    updateCache(address, value);

    // Performing bitwise AND operation between the accumulator (A) and the value
    A &= value;

    // Setting the zero flag if the result is zero
    if (A == 0)
    {
        STATUS |= 0b00100000; // Set Z flag
    }
    else
    {
        STATUS &= ~0b00100000; // Clear Z flag
    }

    // Setting the negative flag if the result's most significant bit is set
    if (A & 0b10000000)
    {
        STATUS |= 0b00000001; // Set N flag
    }
    else
    {
        STATUS &= ~0b00000001; // Clear N flag
    }

    // Displaying the operation
    std::cout << "AND instruction executed. Result stored in accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::EOR(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    uint8_t value = getCachedValue(address);
    if (value == -1)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // Performing bitwise XOR (Exclusive OR) operation between the accumulator (A) and the value
    A ^= value;

    // Setting the zero flag if the result is zero
    if (A == 0)
    {
        STATUS |= 0b00100000; // Set Z flag
    }
    else
    {
        STATUS &= ~0b00100000; // Clear Z flag
    }

    // Setting the negative flag if the result's most significant bit is set
    if (A & 0b10000000)
    {
        STATUS |= 0b00000001; // Set N flag
    }
    else
    {
        STATUS &= ~0b00000001; // Clear N flag
    }

    // Displaying the operation
    std::cout << "EOR instruction executed. Result stored in accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::JMP(RAM &ram, uint16_t instruction_byte)
{
    // Extracting the address from bits 3 to 7 of the instruction byte
    uint16_t address = (instruction_byte & 0b0000111111110000) >> 4;
    // Set the program counter (PC) to the extracted address
    PC = address;

    // Displaying the operation
    std::cout << "JMP instruction executed. Jumping to address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::PSH(RAM &ram)
{
    // Write the accumulator (A) value to the stack at memory location SP
    ram.writeStackByte(SP, A);

    // Increment the stack pointer (SP)
    SP++;

    // Displaying the operation
    std::cout << "PSH instruction executed. Accumulator value pushed onto stack." << std::endl;
}

void CPU::POP(RAM &ram)
{
    // Decrement the stack pointer (SP)
    SP--;

    // Read the value from the stack at memory location SP into the accumulator (A)
    A = ram.readByte(SP);

    // Displaying the operation
    std::cout << "POP instruction executed. Accumulator value popped from stack." << std::endl;
}