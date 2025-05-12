#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

class Memory 
{
    public:
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        uint8_t data[0x10000]; // 64KB of memory
};

#endif