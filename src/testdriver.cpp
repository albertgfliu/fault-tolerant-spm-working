#include <stdio.h>
#include <iostream>
#include <string>

#include <elfio/elfio.hpp>

#include <Instruction.hpp>
#include <AddressParser.hpp>
#include <InstructionParser.hpp>

using namespace FSPM;
using namespace ELFIO;

void
print_usage(char *program_name)
{
    fprintf(stderr, "Usage: %s [-m memory_size] [-o output] input \n", program_name);
}

int
main(int argc, char **argv)
{
    AddressParser ap;
    InstructionParser ip;


}
