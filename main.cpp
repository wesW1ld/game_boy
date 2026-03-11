#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>
#include <bitset>
#include <fstream>


int main()
{
    Memory memory;
    CPU cpu = CPU(memory);

    cpu.readInputFile();

    std::ofstream file("output.out");
    if (!file) 
    {
        std::cout << "Error opening file\n";
        return 1;
    }

    bool loop = true;
    int loops = 0;
    int option;

    while(loop)
    {
        for(int i = 0; i < 8; i++)
        {
            file << static_cast<int>(cpu.registers[i]) << " ";
        }
        file << "\n";
        cpu.step();
        if(cpu.stopped)
        {
            loop = false;
        }

        //bail out if I forget stop command (0x10)
        loops++;
        if(loops > 500)
        {
            loop == false;
        }
    }

    for(int i = 0; i < 8; i++)
    {
        file << static_cast<int>(cpu.registers[i]) << " ";
    }

    file.close();
    return 0;
}
