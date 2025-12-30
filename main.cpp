#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>
#include <bitset>


int main()
{
    Memory memory;
    CPU cpu = CPU(memory);

    cpu.readInputFile();

    bool loop = true;
    int option;

    while(loop)
    {
        for(int i = 0; i < 8; i++)
        {
            std::cout << static_cast<int>(cpu.registers[i]) << " ";
        }
        std::cout << "PC: " << static_cast<int>(cpu.PC()) <<"\n";
        std::cout << "cycles: " << cpu.cycles <<"\n";

        std::cout << "1: step 0: end\n";
        std::cin >> option;
        if(option == 0){loop = false;}
        else
        {
            cpu.step();
        }
    }

    for(int i = 0; i < 8; i++)
    {
        std::cout << static_cast<int>(cpu.registers[i]) << " ";
    }
    std::cout << "\n";

    return 0;
}
