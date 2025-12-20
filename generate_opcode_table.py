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
        f.write(f"    {{ &CPU::{mnemonic} , {bytes_}, {cycles}, \"{mnemonic}\" }},\n")
    for opcode in opcodes["cbprefixed"]:
        mnemonic = opcodes["cbprefixed"][opcode]["mnemonic"]
        cycles = opcodes["cbprefixed"][opcode]["cycles"][0]
        bytes_ = opcodes["cbprefixed"][opcode]["bytes"]
        f.write(f"    {{ &CPU::{mnemonic} , {bytes_}, {cycles}, \"{mnemonic}\" }},\n")

    f.write("};\n")
