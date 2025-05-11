#include "CPU.hpp"
#include <iostream>

int main()
{
    CPU cpu;
    cpu.start();

    int option = 0;

    std::cout << "Pick an option";
    std::cin >> option;
    switch (option)
    {
        case 0:
            //CPU::option0();
            break;
        case 1:
            //CPU::option1();
            break;
        default:
            break;
    }

    return 0;
}
