#include "CPU.hpp"
#include <iostream>

CPU::CPU():RegName{
     "$A", "$F", "$B", "$C", "$D", "$E","$H", "$L", 
} // Initialize RegName with 16 elements
// for f:
//bit name explanation
// 7	z	Zero flag
// 6	n	Subtraction flag (BCD)
// 5	h	Half Carry flag (BCD)
// 4	c	Carry flag
{
    // Initialize registers and program counter
    for (int i = 0; i < 8; ++i)
    {
        registers[i] = 0;
    }
    PC = 0; // Initialize Program Counter to 0
    SP = 0;
}

void CPU::start()
{
    //"using namespace std;" is bad practice
    std::cout << "CPU started.";
}

uint16_t CPU::getPair(int firstAdress) //TODO: add check to make sure pair is valid
{
    return (registers[firstAdress] << 8) | (registers[firstAdress + 1]);
}
