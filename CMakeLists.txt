cmake_minimum_required(VERSION 3.8)
project(NES_Emulator VERSION 1.0.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable (Emulator 
    "src/Emulator.cpp" 
    "src/CPU.cpp"
    "src/RAM.cpp"
)
set_target_properties(Emulator PROPERTIES OUTPUT_NAME SCC)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Emulator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Emulator PRIVATE "headers")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
