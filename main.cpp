#include "CPU.hpp"
#include "MEMORY.hpp"
#include <iostream>

int main()
{
    Memory memory;
    CPU cpu = CPU(memory);
    cpu.start();

    int option = 0;

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
            //CPU::option1();
            break;
        default:
            break;
    }

    return 0;
}
