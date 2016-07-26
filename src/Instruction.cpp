#include <stddef.h>
#include <Instruction.hpp>

using namespace FSPM;

template <class T>
Instruction<T>::Instruction(T rawInstruction, uint32_t elfOffset) :
    m_raw_instruction(rawInstruction),
    m_offset(elfOffset)
{
}

template <class T>
Instruction<T>::~Instruction()
{
}

template <class T>
size_t
Instruction<T>::getSize()
{
    return sizeof(T);
}

template <class T>
uint32_t
Instruction<T>::getType()
{
    return 0;
}

