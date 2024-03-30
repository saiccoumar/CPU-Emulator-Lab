# CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(NES_Emulator VERSION 1.0.0 LANGUAGES C CXX)

# Add executable for Emulator
add_executable(Emulator 
    "src/Emulator.cpp" 
    "src/CPU.cpp"
    "src/RAM.cpp"
)

# Set output name
set_target_properties(Emulator PROPERTIES OUTPUT_NAME SCC)

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Emulator PROPERTY CXX_STANDARD 20)
endif()

# Include directories
target_include_directories(Emulator PRIVATE "headers")

# Add unit tests
add_executable(test_CPU "tests/test_CPU.cpp" "src/CPU.cpp" "src/RAM.cpp")
add_executable(test_RAM "tests/test_RAM.cpp" "src/RAM.cpp")

# Include directories for tests
target_include_directories(test_CPU PRIVATE "headers")
target_include_directories(test_RAM PRIVATE "headers")

# Enable testing
enable_testing()

# Add tests
add_test(NAME test_read_ram COMMAND test_RAM read_ram)
add_test(NAME test_write_instruction_ram COMMAND test_RAM write_instruction)
add_test(NAME test_write_stack_ram COMMAND test_RAM write_stack)
add_test(NAME test_write_byte_ram COMMAND test_RAM write_byte)
add_test(NAME test_cpu_lda COMMAND test_CPU test_lda)
add_test(NAME test_cpu_adc COMMAND test_CPU test_adc)
add_test(NAME test_cpu_sbc COMMAND test_CPU test_sbc)
add_test(NAME test_cpu_and COMMAND test_CPU test_and)
add_test(NAME test_cpu_eor COMMAND test_CPU test_eor)
add_test(NAME test_cpu_jmp COMMAND test_CPU test_jmp)
add_test(NAME test_cpu_psh COMMAND test_CPU test_psh)
add_test(NAME test_cpu_pop COMMAND test_CPU test_pop)
add_test(NAME test_cache_1 COMMAND test_CPU test_cache_1)
add_test(NAME test_cache_2 COMMAND test_CPU test_cache_2)

# CPack settings
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
