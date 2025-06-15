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
