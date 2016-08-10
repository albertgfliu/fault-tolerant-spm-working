#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <stddef.h>
#include <stdint.h>

/* Enumerate for instruction types */

namespace FSPM {

class WordBase
{
  public:
//    WordBase(uint32_t raw, uint32_t offset);
    virtual size_t getSize() = 0;
    uint32_t getOffset();

  protected:
    uint32_t m_raw;
    uint32_t m_offset; //temporary
};

class Instruction : public WordBase {
  public:
    virtual uint32_t getType() = 0;
};

class Instruction16 : public Instruction {
  public:
    size_t getSize();
    uint32_t getType(); 
    uint16_t getRaw();
};

class Instruction32 : public Instruction {
  public:
    size_t getSize();
    uint32_t getType();
    uint32_t getRaw();
};

class Constant : public WordBase {
  public:
    size_t getSize(); // current assumption is constants are 16-bits
    uint16_t getRaw(); // current assumption is constants are 16-bits
};

/*
class InstructionBase
{
  public:
    virtual size_t getSize() = 0;
    virtual uint32_t getType() = 0; // Returns a value from enum based on OpCode
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
    T m_raw_instruction; // Holds raw bytes 
    uint32_t m_offset; // Holds offset of instruction in ELF
    std::vector<Instruction *> m_references;
};

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
} */

} // namespace FSPM

#endif
