#ifndef INSTRUCTIONPARSER_HPP
#define INSTRUCTIONPARSER_HPP

#include <iostream>

namespace FSPM {

class InstructionParser {

  public:
    InstructionParser();
    ~InstructionParser();
    bool loadInstructions(std::istream &instructions);
    bool loadInstructions(char *charBuf);

  private:
    std::istream & charBufToStream(char *charBuf);

};

} // namespace FSPM

#endif
