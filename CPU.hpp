#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

class CPU
{
    public:
        uint8_t registers[8];
        uint16_t PC; // Program Counter
        uint16_t SP; // Stack Pointer
        const char RegName[8][6];

        uint8_t* memory; //pointer to memory which is stored outside of the CPU

        CPU();

        void start();

        //load instructions
        void LD(int reg1, int reg2);
        void LDi(int reg, int value);
        void LD16(int reg1, int reg2);
        void LDtoM(int address, int reg);//load to memory
        void LDM(int reg, int address);//load memory
        void LD16toM(int reg1, int reg2);//copy from reg2 to address at 16 bit reg1
        void LD16toMi(int value, int reg);//value is address
        void LDHi(int reg, int value);//swap above
        void LDHc(int c, int reg);//reg to $FF00+C
        void LD();
        void LD();
        void LDHM(int reg1, int reg2);//at address from reg2 (16bit) to reg1
        void LDHMc(int reg, int c);//$FF00+C to reg
        //4 more, rest of load are stack stuff for later

    private:
    uint16_t getPair(int firstAdress);
};

#endif