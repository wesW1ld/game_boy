import json

with open("opcodes.json", "r") as f:
    opcodes = json.load(f)

with open("OpcodeTable.hpp", "w") as f:
    f.write("#include \"CPU.hpp\"\n\n")
    f.write("#include <iostream>\n\n")
    f.write("struct Opcode {\n")
    f.write("    void (CPU::*func)();\n")
    f.write("    uint8_t bytes;\n")
    f.write("    uint8_t cycles;\n")
    f.write("    const char* mnemonic;\n")
    f.write("};\n\n")

    f.write("Opcode opcodeTable[512] = {\n")


    for opcode in opcodes["unprefixed"]:
        mnemonic = opcodes["unprefixed"][opcode]["mnemonic"]
        cycles = opcodes["unprefixed"][opcode]["cycles"][0]
        bytes_ = opcodes["unprefixed"][opcode]["bytes"]

        func = mnemonic
        if((int(opcode, 16) >= 0x40) and (int(opcode, 16) <= 0x7F)):
            func = "LD_r8_r8"

        f.write(f"    {{ &CPU::{func} , {bytes_}, {cycles}, \"{mnemonic}\" }},//{opcode}\n")
    for opcode in opcodes["cbprefixed"]:
        mnemonic = opcodes["cbprefixed"][opcode]["mnemonic"]
        cycles = opcodes["cbprefixed"][opcode]["cycles"][0]
        bytes_ = opcodes["cbprefixed"][opcode]["bytes"]

        func = mnemonic
        if((int(opcode, 16) >= 0x40) and (int(opcode, 16) <= 0x7F)):
            func = "BIT_r"
        if((int(opcode, 16) >= 0x80) and (int(opcode, 16) <= 0xBF)):
            func = "RES_r"
        if((int(opcode, 16) >= 0xC0) and (int(opcode, 16) <= 0xFF)):
            func = "SET_r"

        f.write(f"    {{ &CPU::{func} , {bytes_}, {cycles}, \"{mnemonic}\" }},//{opcode}\n")

    f.write("};\n")

#above otimizations saves about 256 entries(HALF!!!) from being manually typed