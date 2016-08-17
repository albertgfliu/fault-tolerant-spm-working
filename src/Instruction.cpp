#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <Instruction.hpp>

using namespace FSPM;

//////////WordBase//////////

uint32_t
WordBase::getOffset()
{
    return m_offset;
}

////////////////////////////

//Instruction////////////////

Instruction::~Instruction()
{
    std::vector<WordBase *>::iterator it;
    for (it = references.begin(); it < references.end(); it++) {
        delete (*it);
    }
    references.clear();
}

//Instruction16//////////////

Instruction16::Instruction16(uint16_t raw)
{
    m_raw = (uint32_t) raw;
}

Instruction16::~Instruction16()
{
}

size_t
Instruction16::getSize()
{
    return sizeof(uint16_t);
}

uint32_t
Instruction16::getType()
{
    return 0; //IMPLEMENT ME
}

uint16_t
Instruction16::getRaw()
{
    return (uint16_t) m_raw;
}

//////////////////////////////



//Instruction32////////////////

Instruction32::Instruction32(uint32_t raw)
{
    m_raw = raw;
}

Instruction32::~Instruction32()
{
}

size_t
Instruction32::getSize()
{
    return sizeof(uint32_t);
}

uint32_t
Instruction32::getType()
{
    return 0; //IMPLEMENT ME
}

uint32_t
Instruction32::getRaw()
{
    return (uint32_t) m_raw;
}

/////////////////////////////////


//Constant///////////////////////

Constant::Constant(uint16_t raw)
{
    m_raw = (uint32_t) raw;
}

Constant::Constant(uint32_t raw)
{
    m_raw = raw;
}

Constant::~Constant()
{
}

size_t
Constant::getSize()
{
    return sizeof(uint16_t);
}

uint16_t
Constant::getRaw()
{
    return (uint16_t) m_raw;
}

/////////////////////////////////
