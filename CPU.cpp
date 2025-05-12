#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>

CPU::CPU(Memory& mem):memory(mem), RegName{
     "$A", "$F", "$B", "$C", "$D", "$E","$H", "$L", 
}
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

//load instructions
void CPU::LD_r8_r8(int dest, int src)
{
    registers[dest] = registers[src];
}
void CPU::LD_r8_n8(int dest, uint8_t val)
{
    registers[dest] = val;
}
void CPU::LD_r16_n16(int dest, uint16_t val)
{
    if(dest % 2 == 0)
    {
        registers[dest] = static_cast<uint8_t>(val>>8);
        registers[dest + 1] = static_cast<uint8_t>(val&0xFF);
    }
    else
    {
        std::cout << "Ivalid 16 bit address" << std::endl;
    }
}
void CPU::LD_memHL_r8(int src)
{
    memory.write(getPair(6), registers[src]);
}
void CPU::LD_memHL_n8(uint8_t value)
{
    memory.write(getPair(6), value);
}
void CPU::LD_r8_memHL(int dest)
{
    registers[dest] = memory.read(getPair(6));
}
void CPU::LD_mem_r16_A(uint16_t& dest)
{
    
}
void CPU::LD_mem_n16_A(uint16_t dest);
void CPU::LDH_mem_n16_A(uint16_t dest);
void CPU::LDH_mem_C_A();
void CPU::LD_A_mem_r16(uint16_t& src);
void CPU::LD_A_mem_n16(uint16_t src);
void CPU::LDH_A_mem_n16(uint8_t src);
void CPU::LDH_A_mem_C();
void CPU::LD_mem_HLI_A();
void CPU::LD_mem_HLD_A();
void CPU::LD_A_mem_HLI();
void CPU::LD_A_mem_HLD();

uint16_t CPU::getPair(int firstAdress) //TODO: add check to make sure pair is valid
{
    if(firstAdress % 2 == 0)
    {
        return (registers[firstAdress] << 8) | (registers[firstAdress + 1]);
    }
    else
    {
        std::cout << "Ivalid 16 bit address" << std::endl;
        return 0;
    }
}
