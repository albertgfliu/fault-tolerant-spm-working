#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>

#include <elfio/elfio.hpp>

#include <AddressParser.hpp>
#include <Instruction.hpp>
#include <InstructionParser.hpp>

using namespace FSPM;
using namespace ELFIO;

bool    verbose_flag = false;
char *  input_file_path;
char *  output_file_path;
char *  address_file_path;
int     memory_size = 16384;

void
printUsage(char *program_name)
{
    std::cout << "Usage: " + 
                 std::string(program_name) + 
                 " [-m memory_size] [-o output] input" << std::endl;
}

int
main(int argc, char* argv[])
{
    /* OPTION PARSING SECTION
     * This part of the program parses arguments and sets fields accordingly.
     * This could be modularized in the future, but may be unnecessary.
     */
    
    int c;
    while ((c = getopt(argc, argv, "m:o:v")) != -1) {
        switch (c) {
            case 'm':
                memory_size = atoi(optarg);
                break;
            case 'o':
                output_file_path = optarg;
                break;
            case 'i':
                input_file_path = optarg;
                break;
            case 'v':
                verbose_flag = true;
                break;
            default:
                printUsage(argv[0]);
                return 0;
        }
    }

    if (optind < argc) {
        input_file_path = argv[optind];
        std::cout << "Input File Path: " +
                     std::string(input_file_path) << std::endl;
    }

    std::cout << "Memory Constraint: " + 
                 std::to_string(memory_size) + 
                 " bytes." << std::endl;

    std::cout << "Output File Path: " +
                 std::string(output_file_path) << std::endl;
    
    AddressParser ap;
    InstructionParser ip;

    std::ifstream addressFile; // default mode parameter is ios::in
    addressFile.open("addresses.txt");

    ap.readAddresses(addressFile);

    addressFile.close();

}
