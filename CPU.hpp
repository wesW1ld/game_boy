#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <array>
#include <string>
#include "MEMORY.hpp"

class CPU
{
    public:
        uint8_t registers[12];
        bool IME;  // Interrupt Master Enable flag
        bool pendingEnableIME; // EI sets this, IME becomes true next instruction 
        uint8_t currentOpcode;  

        CPU(Memory& mem);

        void step();

        //load instructions
        void LD_r8_r8();                             // LD r8, r8
        void LD_r8_n8();                         // LD r8, n8
        void LD_r16_n16();                      // LD r16, n16
        void LD_memHL_r8();                                    // LD [HL], r8
        void LD_memHL_n8();                              // LD [HL], n8
        void LD_r8_memHL();                                   // LD r8, [HL]
        void LD_mem_r16_A();                                  // LD [r16], A
        void LD_mem_n16_A();                             // LD [n16], A
        void LDH_mem_n16_A();                            // LDH [n16], A
        void LDH_mem_C_A();                                           // LDH [C], A
        void LD_A_mem_r16();                                  // LD A, [r16]
        void LD_A_mem_n16();                              // LD A, [n16]
        void LDH_A_mem_n16();                              // LDH A, [n16]
        void LDH_A_mem_C();                                           // LDH A, [C]
        void LD_mem_HLI_A();                                          // LD [HLI], A (post-increment)
        void LD_mem_HLD_A();                                          // LD [HLD], A (post-decrement)
        void LD_A_mem_HLI();                                          // LD A, [HLI]
        void LD_A_mem_HLD();                                          // LD A, [HLD]

        //8-bit arithmetic instructions
        void ADC_r();                                          // ADC A, r8
        void ADC_n();                                        // ADC A, n8
        void ADC();                                                   // ADC A, [HL]
        void ADD_r();                                          // ADD A, r8
        void ADD_n();                                        // ADD A, n8
        void ADD();                                                   // ADD A, [HL]
        void CP_r();                                           // CP A,r8
        void CP_n();                                         // CP A,n8
        void CP();                                                    // CP A,[HL]
        void DEC_r();                                          // DEC r8
        void DEC();                                                   // DEC [HL]
        void INC_r();                                          // INC r8
        void INC();                                                   // INC [HL]
        void SBC_r();                                          // SBC A, r8
        void SBC_n();                                        // SBC A, n8
        void SBC();                                                   // SBC A, [HL]
        void SUB_r();                                          // SUB A, r8
        void SUB_n();                                        // SUB A, n8
        void SUB();                                                   // SUB A, [HL]

        //16-bit arithmetic instructions
        void ADD_16();                                        //ADD HL, r16
        void DEC_16();
        void INC_16();

        //Bitwise logic instructions
        void AND_r();                                        //AND A,r8
        void AND_HL();                                              //AND A,[HL]
        void AND_n();                                      //AND A,n8
        void CPL();                                                 //not A
        void OR_r();                                         //OR A,r8
        void OR_HL();                                               //OR A,[HL]
        void OR_n(); 
        void XOR_r();                                       
        void XOR_HL();                                               
        void XOR_n(); 
        
        //Bit flag instructions
        void BIT_r();                               // BIT u3,r8
        void BIT_HL();                                       // BIT u3,[HL]
        void RES_r();                               // RES u3,r8
        void RES_HL();                                       // RES u3,[HL]
        void SET_r();                               // SET u3,r8
        void SET_HL();                                       // SET u3,[HL]

        //Bit shift instructions
        void RL_r();                                         // RL r8
        void RL_HL();                                               // RL [HL]
        void RLA();                                                 // RLA
        void RLC_r();                                        // RLC r8
        void RLC_HL();                                              // RLC [HL]
        void RLCA();                                                // RLCA
        void RR_r();                                         //above but right
        void RR_HL();
        void RRA();
        void RRC_r();
        void RRC_HL();
        void RRCA();
        void SLA_r();
        void SLA_HL();
        void SRA_r();
        void SRA_HL();
        void SRL_r();
        void SRL_HL();
        void SWAP_r();
        void SWAP_HL();

        //Stack manipulation instructions
        void ADD_fSP();                                             //ADD HL,SP
        void ADD_tSP();                                    //ADD SP,e8
        void DEC_SP();                                              //DEC SP
        void INC_SP();                                              //INC SP
        void LD_SP();                                   // LD SP,n16
        void LD_fSP();                              // LD [n16],SP
        void LD_HL();                                      // LD HL,SP+e8
        void LD_fHL();                                              // LD SP,HL
        void POPAF();                                               // POP AF
        void POP();                                         // POP r16
        void PUSHAF();                                              // PUSH AF
        void PUSH();                                        // PUSH r16  

        //Jumps and subroutine instructions
        void CALL(uint16_t address);
        void CALL(int cc, uint16_t address);
        void JPHL();
        void JP(uint16_t address);
        void JP(int cc, uint16_t address);
        void JR(int8_t e8);
        void JR(int cc, int8_t e8);
        void RET(int cc);
        void RET();
        void RETI();
        void RST(uint8_t vec);

        //Interrupt-related instructions
        void DI();
        void EI();
        void HALT();

        //Carry flag instructions
        void CCF();
        void SCF();

        //Miscellaneous instructions
        void DAA();
        void NOP();
        void STOP();

    private:
    uint16_t getPair(int firstAdress);
    int getReg(uint8_t reg);
    int getReg16(uint8_t reg);
    uint8_t imm8();
    uint16_t imm16();
    uint16_t PC();
    Memory& memory;
};

#endif