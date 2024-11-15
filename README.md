# CPU-Emulator-Lab

This is the complete version of the CPU Emulator lab for CS250: Computer Architecture @ Purdue University SP2024. This project was created to familiarize students with the components of a CPU and how to implement them virtually based on their physical designs. Contact me directly for the associated lab handout.

Run Emulator:
```
cmake build build
cmake --build build
./build/SCC.exe
```

View Memory:
```
(in another terminal)
./view_ram.sh
```

Run CPU/RAM Unit Tests:
```
cmake build build
cmake --build build
cd build
ctest
```
