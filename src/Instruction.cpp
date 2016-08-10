#include <stdint.h>
#include <stddef.h>
#include <Instruction.hpp>

using namespace FSPM;

/*WordBase::WordBase(uint32_t raw, uint32_t offset): 
    m_raw(raw), 
    m_offset(offset)
{
}*/

uint32_t
WordBase::getOffset()
{
    return m_offset;
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
