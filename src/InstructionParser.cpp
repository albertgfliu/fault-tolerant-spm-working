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
    membuf sbuf(dataBuf, dataSize);
    std::istream in(&sbuf);
    loadInstructions(in);
}

void
InstructionParser::loadInstructions(std::istream& dataStream)
{
    /* Starting here, check four bytes at a time. If it meets some criteria
        as shown in the old fault-tolerant-spm program, then it is 16-bit
        else it is 32-bit.

        ARM Thumb is by default 16-bit little endian, so a check for 32-bit 
        little endian is necessary. There are no checks for big endian at 
        this time. */
    std::cout << "Got here so far." << std::endl;
}
