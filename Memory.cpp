#include "MEMORY.hpp"

Memory::Memory()
{
    // Initialize memory to zero
    for (int i = 0; i < 0x10000; ++i)
    {
        data[i] = 0;
    }
}
uint8_t Memory::read(uint16_t address) const
{
	return data[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    data[address] = value;
}