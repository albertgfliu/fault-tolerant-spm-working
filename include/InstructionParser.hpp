#ifndef INSTRUCTION_PARSER_HPP
#define INSTRUCTION_PARSER_HPP

#include <iostream>

namespace FSPM {

class InstructionParser {

  public:
    InstructionParser();
    ~InstructionParser();
    void loadInstructions(const char *dataBuf, uint32_t dataSize);
    void loadInstructions(std::istream& dataStream);

  private:
    bool getNextRaw(uint32_t &outRaw, std::istream& dataStream);
    void classify(uint32_t rawIns);
    bool is32Bit(const uint32_t &rawIns);
};

} // namespace FSPM

#endif // INSTRUCTION_PARSER_HPP
