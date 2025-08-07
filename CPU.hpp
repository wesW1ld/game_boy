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
        void LD_A_mem_r16(int dest);                                  // LD A, [r16]
        void LD_A_mem_n16(uint16_t src);                              // LD A, [n16]
        void LDH_A_mem_n16(uint8_t src);                              // LDH A, [n16]
        void LDH_A_mem_C();                                           // LDH A, [C]
        void LD_mem_HLI_A();                                          // LD [HLI], A (post-increment)
        void LD_mem_HLD_A();                                          // LD [HLD], A (post-decrement)
        void LD_A_mem_HLI();                                          // LD A, [HLI]
        void LD_A_mem_HLD();                                          // LD A, [HLD]

        //8-bit arithmetic instructions
        void ADC_r(int src);                                          // ADC A, r8
        void ADC_n(int value);                                        // ADC A, n8
        void ADC();                                                   // ADC A, [HL]
        void ADD_r(int src);                                          // ADD A, r8
        void ADD_n(int value);                                        // ADD A, n8
        void ADD();                                                   // ADD A, [HL]
        void CP_r(int src);                                           // CP A,r8
        void CP_n(int value);                                         // CP A,n8
        void CP();                                                    // CP A,[HL]
        void DEC_r(int src);                                          // DEC r8
        void DEC();                                                   // DEC [HL]
        void INC_r(int src);                                          // INC r8
        void INC();                                                   // INC [HL]
        void SBC_r(int src);                                          // SBC A, r8
        void SBC_n(int value);                                        // SBC A, n8
        void SBC();                                                   // SBC A, [HL]
        void SUB_r(int src);                                          // SUB A, r8
        void SUB_n(int value);                                        // SUB A, n8
        void SUB();                                                   // SUB A, [HL]

        //16-bit arithmetic instructions
        void ADD_16(int src);                                        //ADD HL, r16
        void DEC_16(int dest);
        void INC_16(int dest);

        //Bitwise logic instructions
        void AND_r(int src);                                        //AND A,r8
        void AND_HL();                                              //AND A,[HL]
        void AND_n(int value);                                      //AND A,n8
        void CPL();                                                 //not A
        void OR_r(int src);                                         //OR A,r8
        void OR_HL();                                               //OR A,[HL]
        void OR_n(int value); 
        void XOR_r(int src);                                       
        void XOR_HL();                                               
        void XOR_n(int value); 
        
        //Bit flag instructions
        void BIT_r(int bit, int src);                               // BIT u3,r8
        void BIT_HL(int bit);                                       // BIT u3,[HL]
        void RES_r(int bit, int src);                               // RES u3,r8
        void RES_HL(int bit);                                       // RES u3,[HL]
        void SET_r(int bit, int src);                               // SET u3,r8
        void SET_HL(int bit);                                       // SET u3,[HL]

        //Bit shift instructions
        void RL_r(int src);                                         // RL r8
        void RL_HL();                                               // RL [HL]
        void RLA();                                                 // RLA
        void RLC_r(int src);                                        // RLC r8
        void RLC_HL();                                              // RLC [HL]
        void RLCA();                                                // RLCA
        void RR_r(int src);                                                //above but right
        void RR_HL();
        void RRA();
        void RRC_r(int src);
        void RRC_HL();
        void RRCA();
        void SLA_r(int src);
        void SLA_HL();
        void SRA_r(int src);
        void SRA_HL();
        void SRL_r(int src);
        void SRL_HL();
        void SWAP_r(int src);
        void SWAP_HL();
    private:
    uint16_t getPair(int firstAdress);
    Memory& memory;
};

#endif