#ifndef INSTRUCTION_PARSER_HPP
#define INSTRUCTION_PARSER_HPP

#include <iostream>

namespace FSPM {

class InstructionParser {

  public:
    InstructionParser();
    ~InstructionParser();
    bool loadInstructions(char *dataBuf, uint32_t dataSize);

};

} // namespace FSPM

#endif // INSTRUCTION_PARSER_HPP
