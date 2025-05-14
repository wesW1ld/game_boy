#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <array>
#include <string>
#include "MEMORY.hpp"

class CPU
{
    public:
        uint8_t registers[8];
        uint16_t PC; // Program Counter
        uint16_t SP; // Stack Pointer

        CPU(Memory& mem);

        void start();

        //load instructions
        void LD_r8_r8(int dest, int src);                             // LD r8, r8
        void LD_r8_n8(int dest, uint8_t val);                         // LD r8, n8
        void LD_r16_n16(int dest, uint16_t val);                      // LD r16, n16
        void LD_memHL_r8(int src);                                    // LD [HL], r8
        void LD_memHL_n8(uint8_t value);                              // LD [HL], n8
        void LD_r8_memHL(int dest);                                   // LD r8, [HL]
        void LD_mem_r16_A(int dest);                                  // LD [r16], A
        void LD_mem_n16_A(uint16_t dest);                             // LD [n16], A
        void LDH_mem_n16_A(uint16_t dest);                            // LDH [n16], A
        void LDH_mem_C_A();                                           // LDH [C], A
        void LD_A_mem_r16(int dest);                             // LD A, [r16]
        void LD_A_mem_n16(uint16_t src);                              // LD A, [n16]
        void LDH_A_mem_n16(uint8_t src);                              // LDH A, [n16]
        void LDH_A_mem_C();                                           // LDH A, [C]
        void LD_mem_HLI_A();                                          // LD [HLI], A (post-increment)
        void LD_mem_HLD_A();                                          // LD [HLD], A (post-decrement)
        void LD_A_mem_HLI();                                          // LD A, [HLI]
        void LD_A_mem_HLD();                                          // LD A, [HLD]

    private:
    uint16_t getPair(int firstAdress);
    Memory& memory;
};

#endif