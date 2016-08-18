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

    uint16_t hw1;
    while (getNextRaw(hw1, dataStream) == true) {
        //if we enter the loop, then tmpRawIns is valid. Process it.
        if (is32Bit(hw1)) {
            uint16_t hw2;
            if (getNextRaw(hw2, dataStream) == true) {
                uint32_t raw32Bit = construct32Bit(hw2, hw1);
                Instruction *tmp32 = new Instruction32(raw32Bit);
                instructions.push_back(tmp32);
                std::cout << "Processed a 32-bit word." << std::endl;
                //insert a raw dump on this line
            }
            else {
                std::cout << "Couldn't process upper half-word of 32-bit." 
                          << std::endl;
                break;
            }
        } 
        else { //is 16 bit
            std::cout << "Processed a 16-bit word." << std::endl;
            Instruction *tmp16 = new Instruction16(hw1);
            //insert a raw dump on this line
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
        0b11111, then it is the first halfword of a 32-bit instruction in a
        little-endian encoded executable file. Note: confirm if first halfword 
        means the upper 16 bits or lower 16 bits. Documentation suggests that
        hw1 is the upper half and hw2 is the lower half */

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
    
    //little endian, get lower byte first
    if (!dataStream.get(lower)) { return false; };
    //little endian, get upper byte second
    if (!dataStream.get(upper)) { return false; };

    //construct 16-bit instruction
    outRaw = construct16Bit((uint8_t) lower, (uint8_t) upper);
    printf("%d %d\n", lower, upper);
    return true;
}

uint16_t
InstructionParser::construct16Bit(uint8_t lower, uint8_t upper)
{
    //shift upper byte left, bit-wise OR with lower byte
    return ((((uint16_t) upper) << (sizeof(lower) * 8)) | ((uint16_t) lower));
}

uint32_t
InstructionParser::construct32Bit(uint16_t lower, uint16_t upper)
{
    //shift upper half-word left, bit-wise OR with lower byte
    return ((((uint32_t) upper) << (sizeof(lower) * 8)) | ((uint32_t) lower));
}

