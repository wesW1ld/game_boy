#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>

CPU::CPU(Memory& mem):memory(mem)
// for f:
//bit name explanation
// 7	z	Zero flag
// 6	n	Subtraction flag (BCD)
// 5	h	Half Carry flag (BCD)
// 4	c	Carry flag
// 0-3      Unused(0)
//"$A", "$F", "$B", "$C", "$D", "$E", "$H", "$L"
// 0     1     2     3     4     5     6     7
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
void CPU::LD_mem_r16_A(int dest)
{
    memory.write(getPair(dest), registers[0]);
}
void CPU::LD_mem_n16_A(uint16_t dest)
{
    memory.write(dest, registers[0]);
}
void CPU::LDH_mem_n16_A(uint16_t dest)
{
    if(dest > 0xFF00 && dest < 0xFFFF)
    {
        memory.write(dest, registers[0]);
    }
}
void CPU::LDH_mem_C_A()
{
    memory.write(0xFF00 + registers[3], registers[0]);
}
void CPU::LD_A_mem_r16(int dest)
{
    registers[0] = memory.read(getPair(dest));
}
void CPU::LD_A_mem_n16(uint16_t src)
{
    registers[0] = memory.read(src);
}
void CPU::LDH_A_mem_n16(uint8_t src)
{
    if(src > 0xFF00 && src < 0xFFFF)
    {
        registers[0] = memory.read(src);
    }
}
void CPU::LDH_A_mem_C()
{
    registers[0] = memory.read(0xFF00 + registers[3]);
}
void CPU::LD_mem_HLI_A()
{
    memory.write(getPair(6), registers[0]);
    if(registers[7] == 0xFF)
    {
        registers[7] = 0x00;
        registers[6] += 1;
    }
    else
    {
        registers[7] += 1;
    }
}
void CPU::LD_mem_HLD_A()
{
    memory.write(getPair(6), registers[0]);
    if(registers[7] == 0x00)
    {
        registers[7] = 0xFF;
        registers[6] -= 1;
    }
    else
    {
        registers[7] -= 1;
    }
}
void CPU::LD_A_mem_HLI()
{
    registers[0] = memory.read(getPair(6));
    if(registers[7] == 0xFF)
    {
        registers[7] = 0x00;
        registers[6] += 1;
    }
    else
    {
        registers[7] += 1;
    }
}
void CPU::LD_A_mem_HLD()
{
    registers[0] = memory.read(getPair(6));
    if(registers[7] == 0x00)
    {
        registers[7] = 0xFF;
        registers[6] -= 1;
    }
    else
    {
        registers[7] -= 1;
    }
}

//8-bit arithmetic instructions
void CPU::ADC_r(int src)
{
    CPU::ADC_n(registers[src]);
}
void CPU::ADC_n(int value)
{
    uint8_t initial = registers[0];
    registers[0] += value + ((registers[1] >> 4)& 0b1);
    if(registers[0] == 0)
    {
        registers[1] = 0b1000;  //zero bit
    }
    else
    {
        registers[1] = 0;  //zero bit
    }
    if(initial > registers[0])
    {
        registers[1] += 0b0001; //carry bit
    }
    //          bit 4         +    bit 4   no carry  is not equal  to bit 4 of sum, then there was a carry from before
    if(((((initial >> 4) & 0b1) + ((value >> 4) & 0b1))& 0b1) != ((registers[0] >> 4) & 0b1))
    {
        registers[1] += 0b0010; //half carry bit
    }

    registers[1] = registers[1] << 4; //shift flags into place
}
void CPU::ADC()
{
    CPU::ADC_n(memory.read(getPair(6)));
}
void CPU::ADD_r(int src)
{
    CPU::ADD_n(registers[src]);
}
void CPU::ADD_n(int value)
{
    uint8_t initial = registers[0];
    registers[0] += value;
    if(registers[0] == 0)
    {
        registers[1] = 0b1000;  //zero bit
    }
    else
    {
        registers[1] = 0;  //zero bit
    }
    if(initial > registers[0])
    {
        registers[1] += 0b0001; //carry bit
    }
    //          bit 4         +    bit 4   no carry  is not equal  to bit 4 of sum, then there was a carry from before
    if(((((initial >> 4) & 0b1) + ((value >> 4) & 0b1))& 0b1) != ((registers[0] >> 4) & 0b1))
    {
        registers[1] += 0b0010; //half carry bit
    }

    registers[1] = registers[1] << 4; //shift flags into place
}
void CPU::ADD()
{
    CPU::ADD_n(memory.read(getPair(6)));
}
void CPU::CP_r(int src)
{
    CPU::CP_n(registers[src]);
}
void CPU::CP_n(int value) //add a value ahead to carry from on A, still a problem if value > initial
{
    uint8_t initial = registers[0];
    uint8_t subd = initial - value;

    if(subd == 0)
    {
        registers[1] = 0b1100;  //zero bit
    }
    else
    {
        registers[1] = 0b0100;  //zero bit
    }

    //          bit 4         +    bit 4   no carry  is not equal  to bit 4 of sum, then there was a carry from before
    //if((((((initial >> 4) & 0b1)+0b10) - (((value >> 4) & 0b1)+0b10))& 0b1) != ((subd >> 4) & 0b1))
    if ((initial & 0x0F) < (value & 0x0F)) //better
    {
        registers[1] += 0b0010; //half carry bit
    }

    if(initial < value)
    {
        registers[1] += 0b0001; //carry bit
    }

    registers[1] = registers[1] << 4; //shift flags into place
}
void CPU::CP()
{
    CPU::CP_n(memory.read(getPair(6)));
}
void CPU::DEC_r(int src)
{
    uint8_t initial = registers[src];
    registers[src] -= 1;

    registers[1] = registers[1] & 0x10; //keep current carry flag
    registers[1] |= 0x40; //subtraction flag

    if(registers[src] == 0)
    {
        registers[1] |= 0x80; //zero flag
    }

    if((initial & 0x0F) == 0)
    {
        registers[1] |= 0x20; //half carry flag
    }
}
void CPU::DEC()
{
    uint8_t initial = memory.read(getPair(6));
    memory.write(getPair(6), initial - 1);

    registers[1] = registers[1] & 0x10; //keep current carry flag
    registers[1] |= 0x40; //subtraction flag

    if(initial - 1 == 0)
    {
        registers[1] |= 0x80; //zero flag
    }

    if((initial & 0x0F) == 0)
    {
        registers[1] |= 0x20; //half carry flag
    }
}
void CPU::INC_r(int src)
{
    uint8_t initial = registers[src];
    registers[src] += 1;

    registers[1] = registers[1] & 0x10; //keep current carry flag

    if(registers[src] == 0)
    {
        registers[1] |= 0x80; //zero flag
    }

    if((initial & 0x0F) == 0x0F)
    {
        registers[1] |= 0x20; //half carry flag
    }
}
void CPU::INC()
{
    uint8_t initial = memory.read(getPair(6));
    memory.write(getPair(6), initial + 1);

    registers[1] = registers[1] & 0x10; //keep current carry flag

    if(initial + 1 == 0)
    {
        registers[1] |= 0x80; //zero flag
    }

    if((initial & 0x0F) == 0x0F)
    {
        registers[1] |= 0x20; //half carry flag
    }
}
void CPU::SBC_r(int src)
{
    CPU::SBC_n(registers[src]);
}
void CPU::SBC_n(int value)
{
    //Subtract the value in r8 and the carry flag from A.
    uint8_t initial = registers[0];
    uint8_t carry = ((registers[1] >> 4)& 0b1);
    registers[0] -= (value + carry);

    if(registers[0] == 0)
    {
        registers[1] = 0b1100;  //zero bit
    }
    else
    {
        registers[1] = 0b0100;  //zero bit
    }
    if((value + carry) > initial) //(r8 + carry) > A
    {
        registers[1] += 0b0001; //carry bit
    }
    if ((initial & 0x0F) < ((value & 0x0F) + carry))
    {
        registers[1] += 0b0010; //half carry bit
    }
    
    registers[1] = registers[1] << 4; //shift flags into place
}
void CPU::SBC()
{
    CPU::SBC_n(memory.read(getPair(6)));
}
void CPU::SUB_r(int src)
{
    CPU::SUB_n(registers[src]);
}
void CPU::SUB_n(int value)
{
    uint8_t initial = registers[0];
    registers[0] -= value;

    if(registers[0] == 0)
    {
        registers[1] = 0b1100;  //zero bit
    }
    else
    {
        registers[1] = 0b0100;  //zero bit
    }
    if(value > initial)
    {
        registers[1] += 0b0001; //carry bit
    }
    if ((initial & 0x0F) < (value & 0x0F))
    {
        registers[1] += 0b0010; //half carry bit
    }
    
    registers[1] = registers[1] << 4; //shift flags into place
}
void CPU::SUB()
{
    CPU::SUB_n(memory.read(getPair(6)));
}

//16-bit arithmetic instructions
void CPU::ADD_16(int src) //pass in first source
{
    uint16_t initial = getPair(6);
    uint16_t val = initial + getPair(src);

    registers[6] += static_cast<uint8_t>(val>>8);;//H
    registers[7] += static_cast<uint8_t>(val&0xFF);//L

    registers[1] = registers[1] & 0x80;
    if(val < initial)
    {
        registers[0] |= 0x10; //carry flag
    }

    if(((((initial >> 8) & 0b1) + (((val - initial) >> 8) & 0b1))& 0b1) != ((val >> 8) & 0b1))
    {
        registers[0] |= 0x20; //half carry flag
    }
}

uint16_t CPU::getPair(int firstAdress) //TODO: stop code on error
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
