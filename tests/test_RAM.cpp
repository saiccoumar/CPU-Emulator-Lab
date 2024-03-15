// test_RAM.cpp
#include <iostream>
#include <string>
#include "RAM.h"

// Function to test reading from valid memory address
bool testValidMemoryAddress() {
    // Value in empty memory at memory address 0x200 should be 0
    RAM ram;
    uint8_t value = ram.readByte(0x200);
    if (value == 0x00) {
        std::cout << "Test reading from valid memory address passed." << std::endl;
        return true;
    } else {
        std::cout << "Test reading from valid memory address failed." << std::endl;
        return false;
    }
}

// Function to test reading from invalid memory address
bool testInvalidMemoryAddress() {
    // Value should be -1 to indicate an error has occured
    RAM ram;
    uint8_t value = ram.readByte(0xFFFF);
    if (value == 0xFF) { 
        std::cout << "Test reading from invalid memory address passed." << std::endl;
        return true;
    } else {
        std::cout << "Test reading from invalid memory address failed." << std::endl;
        return false;
    }
}

bool testInvalidWriteInstructionByte(){
    // Write to memory address 257. Error occurs and value at 257 should stay 0.
    RAM ram;
    ram.writeInstructionByte(0x101, 0x01);
    uint8_t value = ram.readByte(0x101);
    if (value == 0x00) { 
        std::cout << "Test writing instruction to memory outside memory space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside memory space failed." << std::endl;
        return false;
    }
}

bool testValidWriteInstructionByte(){
    // Write to memory address 0. No error occurs and value at 0 should be overwritten to 1.
    RAM ram;
    ram.writeInstructionByte(0x00, 0x01);
    uint8_t value = ram.readByte(0x00);
    if (value == 0x01) { 
        std::cout << "Test writing instruction to memory outside memory space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside memory space failed." << std::endl;
        return false;
    }
}

bool testInvalidWriteStackByte1(){
    // Write to memory address 0. Error occurs and value at 0 should stay 0.
    RAM ram;
    ram.writeStackByte(0x00, 0x01);
    uint8_t value = ram.readByte(0x00);
    if (value == 0x00) { 
        std::cout << "Test writing instruction to memory outside stack space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside stack space failed." << std::endl;
        return false;
    }
}

bool testInvalidWriteStackByte2(){
    // Write to memory address 513. Error occurs and value at 513 should stay 0.
    RAM ram;
    ram.writeStackByte(0x201, 0x01);
    uint8_t value = ram.readByte(0x201);
    if (value == 0x00) { 
        std::cout << "Test writing instruction to memory outside stack space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside stack space failed." << std::endl;
        return false;
    }
}

bool testValidWriteStackByte(){
    // Write to memory address 300. No error occurs and value at 300 should be overwritten to 1.
    RAM ram;
    ram.writeStackByte(0x12C, 0x01);
    uint8_t value = ram.readByte(0x12C);
    if (value == 0x01) { 
        std::cout << "Test writing instruction to memory outside stack space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside stack space failed." << std::endl;
        return false;
    }
}

bool testInvalidWriteByte(){
    // Write to memory address 0. Error occurs and value at 0 should stay 0.
    RAM ram;
    ram.writeByte(0x00, 0x01);
    uint8_t value = ram.readByte(0x00);
    if (value == 0x00) { 
        std::cout << "Test writing instruction to memory outside stack space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside stack space failed." << std::endl;
        return false;
    }
}
bool testValidWriteByte(){
    // Write to memory address 512. Error occurs and value at 0 should stay 0.
    RAM ram;
    ram.writeByte(0x200, 0x01);
    uint8_t value = ram.readByte(0x200);
    if (value == 0x01) { 
        std::cout << "Test writing instruction to memory outside stack space passed." << std::endl;
        return true;
    } else {
        std::cout << "Test writing instruction to memory outside stack space failed." << std::endl;
        return false;
    }
}



int main(int argc, char* argv[]) {
    int tests_passed = 0;
    int total_tests = 0;

    // Check if specific tests are requested via command-line arguments
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "all")) {
        // Run all tests
        total_tests = 7;
        if (testValidMemoryAddress())
            tests_passed++;
        if (testInvalidMemoryAddress())
            tests_passed++;
        if (testInvalidWriteInstructionByte())
            tests_passed++;
        if (testValidWriteInstructionByte())
            tests_passed++;
        if (testInvalidWriteStackByte1())
            tests_passed++;
        if (testInvalidWriteStackByte2())
            tests_passed++;
        if (testValidWriteStackByte())
            tests_passed++;
    } else if (argc == 2 && std::string(argv[1]) == "read_ram") {
        total_tests = 2;
        if (testValidMemoryAddress())
            tests_passed++;
        if (testInvalidMemoryAddress())
            tests_passed++;
    } else if (argc == 2 && std::string(argv[1]) == "write_instruction") {
        total_tests = 2;
        if (testInvalidWriteInstructionByte())
            tests_passed++;
        if (testValidWriteInstructionByte())
            tests_passed++;
    }else if (argc == 2 && std::string(argv[1]) == "write_stack") {
        total_tests = 3;
        if (testInvalidWriteStackByte1())
            tests_passed++;
        if (testInvalidWriteStackByte2())
            tests_passed++;
        if (testValidWriteStackByte())
            tests_passed++;
    }else if (argc == 2 && std::string(argv[1]) == "write_byte") {

        total_tests = 2;
        if (testInvalidWriteByte())
            tests_passed++;
        if (testValidWriteByte())
            tests_passed++;
    }else {
        std::cerr << "Invalid command-line arguments. Usage: test_RAM [all|valid|invalid]" << std::endl;
        return 1;
    }

    std::cout << "Total passed tests: " << tests_passed << "/" << total_tests << std::endl;

    // Return exit code based on tests passed/failed
    return (tests_passed == total_tests) ? 0 : 1;
}
