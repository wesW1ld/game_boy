#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>
#include <bitset>

int main()
{
    Memory memory;
    CPU cpu = CPU(memory);
    cpu.start();

    int option = 0;

    while(option != 9)
    {
        std::cout << "Pick an option";
        std::cin >> option;
        switch (option)
        {
            case 0:
                std::cout << (int)memory.read(0) << std::endl;
                cpu.LD_memHL_n8(0xFF);
                std::cout << (int)memory.read(0) << std::endl;
                break;
            case 1:
                cpu.registers[2] = 0x0F; //set B to 0xFF
                cpu.registers[0] = 0x0F; //set A to 0xFF
                cpu.ADD_r(2); //add B to A
                std::cout << (int)memory.read(0) << std::endl; //print mem
                cpu.LD_memHL_r8(0);  //add A to first memory address
                std::cout << (int)memory.read(0) << std::endl; //print meme
                std::cout << (int)cpu.registers[1] << std::endl; //print flags
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;
                break;
            case 2:
                cpu.registers[0] = 0x10; //set A
                cpu.registers[1] = 0;
                cpu.SBC_n(0x00); //A - value
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                cpu.registers[0] = 0x10; //set A
                cpu.registers[1] = 0;
                cpu.SBC_n(0x08); //A - value
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                cpu.registers[0] = 0x10; //set A
                cpu.registers[1] = 0;
                cpu.SBC_n(0x20); //A - value
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                cpu.registers[0] = 0x10; //set A
                cpu.registers[1] = 0;
                cpu.SBC_n(0x28); //A - value
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                break;
            case 3:
                cpu.LD_memHL_n8(0x10);
                std::cout << (int)memory.read(0) << std::endl; //print mem
                cpu.DEC();
                std::cout << (int)memory.read(0) << std::endl; //print mem
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                cpu.DEC();
                std::cout << (int)memory.read(0) << std::endl; //print mem
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //print flags
                break;
            case 4:
                cpu.registers[6] = 0x0F;
                cpu.registers[7] = 0xFF;
                cpu.registers[2] = 0x00; // B
                cpu.registers[3] = 0x01; // C

                cpu.ADD_16(2); // HL += BC
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;

                cpu.registers[6] = 0xFF;
                cpu.registers[7] = 0xFF;
                cpu.registers[4] = 0x00; // D
                cpu.registers[5] = 0x01; // E

                cpu.ADD_16(4); // HL += DE
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;

                cpu.registers[6] = 0x0F;
                cpu.registers[7] = 0xFF;
                cpu.registers[4] = 0xF0; // D
                cpu.registers[5] = 0x01; // E

                cpu.ADD_16(4); // HL += DE
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;
                break;
            case 5:
                cpu.registers[4] = 0xF0; // D
                cpu.registers[5] = 0x00; // E
                cpu.DEC_16(4);
                std::cout << std::bitset<8>(cpu.registers[4]) << std::endl;
                std::cout << std::bitset<8>(cpu.registers[5]) << std::endl;
                cpu.INC_16(4);
                std::cout << std::bitset<8>(cpu.registers[4]) << std::endl;
                std::cout << std::bitset<8>(cpu.registers[5]) << std::endl;
                break;
            case 6:
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //0000
                cpu.BIT_r(3, 4);
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //1010
                cpu.registers[1] += 0x10;
                cpu.registers[4] = 0x04;
                cpu.BIT_r(3, 4);
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl; //0011

                //cpu.registers[4] = 0xFF;
                std::cout << std::bitset<8>(cpu.registers[4]) << std::endl;
                cpu.SET_r(3, 4);
                cpu.SET_r(7, 4);
                std::cout << std::bitset<8>(cpu.registers[4]) << std::endl;
                break;
            case 7:
                cpu.registers[1] = 0x10;
                memory.write(0, 0b01000110);
                cpu.RL_HL();
                std::cout << std::bitset<8>(memory.read(0)) << std::endl;
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;
                cpu.registers[1] = 0x10;
                memory.write(0, 0b11000110);
                cpu.RL_HL();
                std::cout << std::bitset<8>(memory.read(0)) << std::endl;
                std::cout << std::bitset<8>(cpu.registers[1]) << std::endl;
                break;
            default:
                uint8_t a = 0b00001000;
                uint8_t b = 0b00100100;
                uint8_t c = a - b;
                std::cout << std::bitset<8>(c) << std::endl;
                option = 9;
                break;
        }

    }

    return 0;
}
