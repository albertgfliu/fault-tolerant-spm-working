#include <stdio.h>
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
    
    //temporary until code entry point is solved
    //dataStream.seekg(0, std::ios_base::beg);
    
    std::vector<Instruction *> instructions;

    uint16_t tmpRawIns;
    while (getNextRaw(tmpRawIns, dataStream) == true) {
        //if we enter the loop, then tmpRawIns is valid. Process it.
        if (is32Bit(tmpRawIns)) {
            uint16_t upperRawIns;
            if (getNextRaw(upperRawIns, dataStream) == true) {
                uint32_t raw32Bit = construct32Bit(tmpRawIns, upperRawIns);
                Instruction *tmp32 = new Instruction32();
                instructions.push_back(tmp32);
            }
            else {
                std::cout << "Couldn't process lower half-word of 32-bit." << std::endl;
                break;
            }
            std::cout << "Got something that's 32-bit." << std::endl;
        } 
        else { //is 16 bit
            std::cout << "Got something that's 16-bit." << std::endl;
            Instruction *tmp16 = new Instruction16();
            instructions.push_back(tmp16);
        }
    }
    std::cout << "Finished parsing instructions." << std::endl;

}

void
InstructionParser::classify(uint32_t rawIns)
{
}

bool
InstructionParser::is32Bit(const uint16_t &rawIns)
{
    /*  This function is an ARM Thumb specific check. Change/remove this 
        function for other architectures (if necessary). */

    /*  If bits [15:11] of half-word being decoded are 0b11101, 0b11110, or 
        0b11111, then it is the lower half of a 32-bit instruction. */

    //If bits [15:13] are not 1s, it is not 32-bit
    if ((rawIns & 0xE000) != 0xE000) { return false; }

    //Now if [12:11] are 0s, it is not 32-bit
    if ((rawIns & 0xF800) == 0xE000) { return false; }

    //Otherwise, it must be 32-bit
    return true;
}

bool
InstructionParser::getNextRaw(uint16_t &outRaw, std::istream& dataStream)
{
    outRaw = 0;
    char lower, upper;
    
    if (!dataStream.get(lower)) { return false; };
    if (!dataStream.get(upper)) { return false; };

    outRaw = construct16Bit((uint8_t) lower, (uint8_t) upper);
    printf("%d %d\n", lower, upper);
    return true;
}

uint16_t
InstructionParser::construct16Bit(uint8_t lower, uint8_t upper)
{
    return ((((uint16_t) upper) << (sizeof(lower) * 8)) & ((uint16_t) lower));
}

uint32_t
InstructionParser::construct32Bit(uint16_t lower, uint16_t upper)
{
    return ((((uint32_t) upper) << (sizeof(lower) * 8)) & ((uint32_t) lower));
}

