#include <iostream>
#include <string>
#include "CPU.h"

bool testLDA()
{
    RAM ram;
    CPU cpu;
    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);

    if (cpu.A == 0x01)
    {
        std::cout << "Test LDA passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "cpu.A = " << std::hex << static_cast<int>(cpu.A) << std::endl;
        std::cout << "Test LDA failed." << std::endl;
        return false;
    }
}

bool testADC()
{
    // Load A = 0x01. Add A to value at 0x200 (0x01). 0x01 + 0x01 = 0x02
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    cpu.ADC(ram, 0x200);

    uint8_t value = ram.readByte(0x200);
    if (value == 0x02)
    {
        std::cout << "Test ADC passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test ADC failed." << std::endl;
        return false;
    }
}

bool testSBC()
{
    // Load A = 0x01. Add A to value at 0x200 (0x01). 0x01 + 0x01 = 0x02
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    uint8_t value = ram.readByte(0x200);
    std::cout << "Value Before SBC = " << std::hex << static_cast<int>(value) << std::endl;
    cpu.SBC(ram, 0x200);

    value = ram.readByte(0x200);
    if (value == 0x00)
    {
        std::cout << "Test SBC passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test SBC failed." << std::endl;
        return false;
    }
}

bool testAND()
{
    // Load A = 0x01. do A AND value at 0x300.
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    cpu.AND(ram, 0x300);

    uint8_t value = ram.readByte(0x300);
    if (cpu.A == 0x00)
    {
        std::cout << "Test AND passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test AND failed." << std::endl;
        return false;
    }
}

bool testEOR()
{
    // Load A = 0x01. do A EOR value at 0x300.
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    cpu.EOR(ram, 0x300);

    uint8_t value = ram.readByte(0x300);
    if (cpu.A == 0x01)
    {
        std::cout << "Test OR passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test OR failed." << std::endl;
        return false;
    }
}

bool testJMP()
{
    // Load A = 0x01. do A EOR value at 0x300.
    RAM ram;
    CPU cpu;

    cpu.JMP(ram, 0x000F);


    if (cpu.PC == 0x000F)
    {
        std::cout << "Test JMP passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "cpu.PC = " << std::hex << static_cast<int>(cpu.PC) << std::endl;
        std::cout << "Test JMP failed." << std::endl;
        return false;
    }
}

bool testPSH()
{
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    cpu.PSH(ram);

    uint8_t value = ram.readByte(0x100);
    if ((value == 0x01) && (cpu.SP = 0x101))
    {
        std::cout << "Test PSH passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test PSH failed." << std::endl;
        return false;
    }
}

bool testPOP()
{
    RAM ram;
    CPU cpu;

    ram.writeByte(0x200, 0x01);
    cpu.LDA(ram, 0x200);
    cpu.PSH(ram);

    cpu.LDA(ram, 0x300);
    cpu.POP(ram);

    uint8_t value = ram.readByte(0x100);
    if ((value == 0x01) && (cpu.SP = 0x100))
    {
        std::cout << "Test POP passed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Value = " << std::hex << static_cast<int>(value) << std::endl;
        std::cout << "Test POP failed." << std::endl;
        return false;
    }
}

int main(int argc, char *argv[])
{
    int tests_passed = 0;
    int total_tests = 0;
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "all"))
    {
        total_tests = 5;
        if (testADC())
            tests_passed++;
        if (testLDA())
            tests_passed++;
        if (testSBC())
            tests_passed++;
        if (testAND())
            tests_passed++;
        if (testEOR())
            tests_passed++;
        if (testJMP())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_adc")
    {

        total_tests = 1;
        if (testADC())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_lda")
    {

        total_tests = 1;
        if (testLDA())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_sbc")
    {

        total_tests = 1;
        if (testSBC())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_and")
    {

        total_tests = 1;
        if (testAND())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_eor")
    {

        total_tests = 1;
        if (testEOR())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_jmp")
    {

        total_tests = 1;
        if (testJMP())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_psh")
    {

        total_tests = 1;
        if (testPSH())
            tests_passed++;
    }
    else if (argc == 2 && std::string(argv[1]) == "test_pop")
    {

        total_tests = 1;
        if (testPOP())
            tests_passed++;
    }

    else
    {
        std::cerr << "Invalid command-line arguments. Usage: test_RAM [all|valid|invalid]" << std::endl;
        return 1;
    }

    std::cout << "Total passed tests: " << tests_passed << "/" << total_tests << std::endl;
    // Return exit code based on tests passed/failed
    return (tests_passed == total_tests) ? 0 : 1;
}