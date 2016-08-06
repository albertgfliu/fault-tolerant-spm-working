#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>

#include <elfio/elfio.hpp>

#include <AddressParser.hpp>
#include <Instruction.hpp>
#include <InstructionParser.hpp>
#include <MainUtils.hpp>

using namespace FSPM;
using namespace ELFIO;

bool    verbose_flag = false;
char *  input_file_path = NULL;
char *  output_file_path = NULL;
char *  address_file_path = NULL;
int     memory_size = 16384;

void
printUsage(char *program_name)
{
    std::cout << "Usage: " + 
                 std::string(program_name) + 
                 "-a faulty address file -o output -i input \
                  [-m memory size]" << std::endl;
}

int
main(int argc, char* argv[])
{
    /* OPTION PARSING SECTION
     * This part of the program parses arguments and sets fields accordingly.
     * This could be modularized in the future, but may be unnecessary.
     */
    
    int c;
    while ((c = getopt(argc, argv, "a:i:m:o:v")) != -1) {
        switch (c) {
            case 'a':
                address_file_path = optarg;
                break;
            case 'i':
                input_file_path = optarg;
                break;
            case 'm':
                memory_size = atoi(optarg);
                break;
            case 'o':
                output_file_path = optarg;
                break;
            case 'v':
                verbose_flag = true;
                break;
            default:
                printUsage(argv[0]);
                return -1;
        }
    }

    if (optind < argc) {
        input_file_path = argv[optind];
    }

    if (address_file_path == NULL ||
        input_file_path == NULL ||
        output_file_path == NULL) {
        printUsage(argv[0]);
        return -1;
    } else {

        std::cout << "Address File Path: " + 
                     std::string(address_file_path) << std::endl;

        std::cout << "Input File Path: " +
                     std::string(input_file_path) << std::endl;
    
        std::cout << "Output File Path: " +
                     std::string(output_file_path) << std::endl;
    
        std::cout << "Memory Constraint: " + 
                     std::to_string(memory_size) + 
                     " bytes." << std::endl;
    }

    /* Load faulty addresses file */    
    AddressParser ap;

    std::ifstream addressFile; // default mode parameter is ios::in
    addressFile.open(std::string(address_file_path));

    ap.readAddresses(addressFile);
    ap.alignAddresses();
    ap.sortAddresses();
    ap.removeDuplicateAddresses();
    ap.filterRange(536870912, 536880000); //test
    ap.printAddresses();

    addressFile.close();

    /* Load ELF file */
    elfio reader;
    if (!reader.load(input_file_path)) {
        std::cout << "Could not process provided ELF file." << std::endl;
        return -1;
    }
    if (reader.get_encoding() == ELFDATA2MSB) {
        std::cout << "Can not process big-endian ELF file." << std::endl;
        return -1;
    }

    //Elf_Half sec_num = reader.sections.size();
    //std::cout << "Number of sections: " << sec_num << std::endl;

    /* Find the code section */
    const section *codesection = getSectionByName(reader, ".text");

    InstructionParser ip;
    if (codesection != nullptr) {
        ip.loadInstructions(codesection->get_data(), codesection->get_size());
    }

    std::cout << codesection->get_size() << std::endl;
}
