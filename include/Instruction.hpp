#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <stddef.h>
#include <stdint.h>

/* Enumerate for instruction types */

namespace FSPM {

class InstructionBase
{
  public:
    virtual ~InstructionBase();
    virtual size_t getSize() = 0;
    virtual uint32_t getType() = 0; /* Returns a value from enum based on OpCode */
};

template<class T>
class Instruction : public InstructionBase
{
  public:
    Instruction(T rawInstruction, uint32_t elfOffset);
    ~Instruction();
    size_t getSize();
    uint32_t getType();

  private:
    T        m_raw_instruction; /* Holds the raw instruction in bytes */
    uint32_t m_offset; /* Holds the offset of the instruction in the ELF */
};

} // namespace FSPM

#endif
