#include <iostream>
#include <InstructionParser.hpp>
#include <ThumbIsa.hpp>
#include <MemStream.hpp> //for membuf

using namespace FSPM;

InstructionParser::InstructionParser()
{
}

InstructionParser::~InstructionParser()
{
}

void
InstructionParser::loadInstructions(const char *dataBuf, uint32_t dataSize)
{
    membuf sbuf(dataBuf, dataBuf + dataSize);
    std::istream in(&sbuf);
    loadInstructions(in);
}

void
InstructionParser::loadInstructions(std::istream& dataStream)
{
    std::cout << "Got here so far." << std::endl;
}
