#include <AddressParser.hpp>
#include <algorithm>
#include <vector>

using namespace FSPM;

AddressParser::AddressParser()
{
}

bool
AddressParser::readAddresses(std::istream& addressStream)
{
    //dynamically allocate read buffer inside here
    //jump to start of stream

    //read line by line until EOF
    //if bad format found, then break by returning false
    //otherwise, encode into numerical format and push_back into bad_addresses
    return true;
}

std::vector<uint32_t> *
AddressParser::getBadAddresses()
{
    return &bad_addresses;
}

void
AddressParser::sortAddresses()
{
    sort(bad_addresses.begin(), bad_addresses.end());
}

bool
AddressParser::align_bad_address(uint32_t &addr)
{
    addr -= (addr % sizeof(addr));
}

/* Relevant code from the main driver below */

/*
    * SECTION 2: ADDRESS PARSING SECTION
     * This part of the program parses an address file given paths from
     * the previous section for option parsing.
     *
     * Addresses.txt is a text file with hex representations of 32-bit 
     * addresses.
     *
     * Each 32-bit address is 8 hex characters prefixed by 0x.
     * Each address is separated from other addresses by newlines or 
     * whitespaces. 
     * 
     * e.g., when Addresses.txt is opened by notepad, it will show:
     * 0x040302AF
     * 0x28EA1423
     * 0x00FF0243
     *

    * Parse addresses *
    if (input_file_path == NULL) {
        fprintf(stderr, "Input file is required\n");
        print_usage();
        exit(EXIT_FAILURE);
    }

    FILE* address_file;
    address_file = fopen(input_file_path, "r");
    if (address_file == NULL) {
        fprintf(stderr, "Error: address file does not exist in input file path or cannot be opened\n");
        return -1;
    }
    VPRINTF("%s\n", "Address file has been opened");

    * Load from addresses.txt into bad_addrs*
    vector<unsigned int> bad_addrs;
    char* address_buff = new char[16];

    VPRINTF("%s", "Loading addresses\n");
    while (!feof(address_file)) {
        //fscanf(address_file, "0x%8c ", address_buff);
        if (fscanf(address_file, "%s", address_buff) == EOF) {
            break;
        }
        string address_str = address_buff;
        //printf("%s\n", address_str.c_str());
        unsigned int numeric_address = (unsigned int) stoul(address_str, nullptr, 16);
        VPRINTF("%d\n", numeric_address);
        //printf("0x%08x\n", numeric_address);
        if (numeric_address < SRAM_START || numeric_address >= (SRAM_START + memory_size)) {
            fprintf(stderr, "The address %s is not within SRAM range\n", address_str.c_str());
        }
        else {
            bad_addrs.push_back(numeric_address);
        }
    }

    sort(bad_addrs.begin(), bad_addrs.end());

    //for_each(bad_addrs.begin(), bad_addrs.end(), print_item);

    VPRINTF("%s\n", "Addresses successfully loaded");
    //printf("There are %u bad addresses\n", (unsigned int)bad_addrs.size());

    //clean up address parsing
    delete[] address_buff;
    int fcloseerr;
    if ((fcloseerr = fclose(address_file)) != 0) {
        fprintf(stderr, "Error: failed to close address file\n");
        return fcloseerr;
    }
    VPRINTF("%s\n", "Address file has been closed");


*/