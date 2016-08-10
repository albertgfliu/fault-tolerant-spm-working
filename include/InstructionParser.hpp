#ifndef INSTRUCTION_PARSER_HPP
#define INSTRUCTION_PARSER_HPP

#include <iostream>
#include <vector>
#include <Instruction.hpp>

namespace FSPM {

class InstructionParser {

  public:
    InstructionParser();
    ~InstructionParser();
    void loadInstructions(const char *dataBuf, uint32_t dataSize);
    void loadInstructions(std::istream& dataStream);

  private:
    bool getNextRaw(uint16_t &outRaw, std::istream& dataStream);
    void classify(uint32_t rawIns);
    bool is32Bit(const uint16_t &rawIns);
    uint16_t construct16Bit(uint8_t lower, uint8_t upper);
    uint32_t construct32Bit(uint16_t lower, uint16_t upper);

    std::vector<Instruction> instructions;
    
};

} // namespace FSPM

#endif // INSTRUCTION_PARSER_HPP
