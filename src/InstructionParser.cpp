#include <iostream>
#include <InstructionParser.hpp>
#include <ThumbIsa.hpp>
#include <MemStream.hpp> //for membuf
#include <Instruction.hpp>

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

    uint32_t tmpRawIns;
    while (getNextRaw(tmpRawIns, dataStream) == true) {
        //if we enter the loop, then tmpRawIns is valid. Process it.
        if (is32Bit(tmpRawIns)) {
            //then do one more processing sequence, shoving into upper bits
        } 
        else { //is 16 bit
            //dynamically allocate Instruction and push_back
            uint16_t tmp16RawIns = (uint16_t) tmpRawIns;
            Instruction<uint16_t> * tmpIns = 
                new Instruction<uint16_t>(tmp16RawIns, dataStream.tellg());
            
        }
    }
    std::cout << "I guess we are done parsing." << std::endl;
}

void
InstructionParser::classify(uint32_t rawIns)
{
}

bool
InstructionParser::is32Bit(const uint32_t &rawIns)
{
    /*  This function is an ARM Thumb specific check. Change/remove this 
        function for other architectures (if necessary). */

    //if bits [15:11] of half-word being decoded are 0b11101, 0b11110, or 0b11111, it's the first half-word of a 32-bit instruction

    //to do this, first check if bits [15:13] are 1's, it's not 32-bit
    if ((rawIns & 0xE000) != 0xE000) { return false; }

    //then check if [12:11] are 0s, not 32-bit
    if ((rawIns & 0xF800) == 0xE000) { return false; }

    //if conditions are all fulfilled, it is 32-bit 
    return true;
}

bool
InstructionParser::getNextRaw(uint32_t &outRaw, std::istream& dataStream)
{
    return false;
}
