#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>

int main()
{
    Memory memory;
    CPU cpu = CPU(memory);
    cpu.start();

    int option = 0;

    while(option != 2)
    {
        std::cout << "Pick an option" << std::endl;
        std::cin >> option;
        switch (option)
        {
            case 0:
                std::cout << (int)memory.read(0) << std::endl;
                cpu.LD_memHL_n8(0xFF);
                std::cout << (int)memory.read(0) << std::endl;
                break;
            case 1:
                cpu.registers[2] = 0xFF; //set B to 0xFF
                cpu.ADC_r(2); //add B to A
                std::cout << (int)memory.read(0) << std::endl; //print mem
                cpu.LD_memHL_r8(0);  //add A to first memory address
                std::cout << (int)memory.read(0) << std::endl; //print meme
                std::cout << cpu.registers[1] << std::endl; //print flags
                break;
            default:
                option = 2;
                break;
        }

    }

    return 0;
}
