#ifndef INSTRUCTION_PARSER_HPP
#define INSTRUCTION_PARSER_HPP

#include <iostream>

namespace FSPM {

class InstructionParser {

  public:
    InstructionParser();
    ~InstructionParser();
    bool loadInstructions(char *dataBuf, uint32_t dataSize);

  private:
    void classify(uint32_t rawIns);

};

} // namespace FSPM

#endif // INSTRUCTION_PARSER_HPP
