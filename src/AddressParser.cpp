#include <AddressParser.hpp>
#include <algorithm>        //std::unique, std::sort
#include <vector>
#include <iostream>
#include <regex>

using namespace FSPM;

AddressParser::AddressParser()
{
}

AddressParser::~AddressParser()
{
}

bool
AddressParser::readAddresses(std::istream& addressStream)
{
    bool retval = true;
    
    //jump to start of stream
    addressStream.seekg(addressStream.beg);

    //parse through stream using regex
    while (true) {
        std::string addrString;
        if (!std::getline(addressStream, addrString)) {
            break;
        }
        
        std::regex reg0("(0x){0,1}[a-fA-F0-9]{1,8}", 
                        std::regex_constants::icase);
        std::sregex_iterator it(addrString.begin(), addrString.end(), reg0);
        std::sregex_iterator it_end;

        while (it != it_end) {
//            std::cout << (*it).str() + " ";
            uint32_t addr = (uint32_t) std::stoul((*it).str(), nullptr, 16);
            bad_addresses.push_back(addr);
            ++it;
        }

    }

    return retval;
}

std::vector<uint32_t> *
AddressParser::getBadAddresses()
{
    return &bad_addresses;
}

void
AddressParser::sortAddresses()
{
    std::sort(bad_addresses.begin(), bad_addresses.end());
}

void
AddressParser::align_bad_address(uint32_t &addr)
{
    addr -= (addr % sizeof(addr));
}

void
AddressParser::alignAddresses()
{
    std::vector<uint32_t>::iterator it;

    for(it = bad_addresses.begin(); it < bad_addresses.end(); it++) {
        align_bad_address(*it);
    }
}

void
AddressParser::removeDuplicateAddresses()
{
    /* This implementation assumes addresses are not sorted, and will sort them
     * again. Ordering is consequently not guaranteed to be preserved.
     */
    
    sortAddresses();

    bad_addresses.erase(std::unique(bad_addresses.begin(), bad_addresses.end()),
                        bad_addresses.end());

}

void
AddressParser::printAddresses()
{
    std::vector<uint32_t>::iterator it;

    for (it = bad_addresses.begin(); it < bad_addresses.end(); it++) {
        std::cout << (*it) << std::endl;
        

    }

}

void
AddressParser::filterRange(uint32_t begin, uint32_t end)
{
    bad_addresses.erase(std::remove_if(bad_addresses.begin(), 
                                        bad_addresses.end(), 
                                        [&](const uint32_t x) {
                                            return ((x < begin) || (x >= end));
                                        }), 
                        bad_addresses.end());
}
