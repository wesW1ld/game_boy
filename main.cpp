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
        std::cout << "1: step 0: end\n";
        std::cin >> option;
        if(option == 0){loop = false;}
        else
        {
            cpu.step();
        }
    }

    return 0;
}
