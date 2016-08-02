#ifndef ADDRESS_PARSER_HPP
#define ADDRESS_PARSER_HPP

/* C includes */
#include <stdint.h>

/* C++ includes */
#include <vector>
#include <iostream>

namespace FSPM {

class AddressParser
{
  public:
    AddressParser();
    ~AddressParser();
    bool readAddresses(std::istream& addressStream);
    std::vector<uint32_t> * getBadAddresses();
    void sortAddresses();

  private:
    std::vector<uint32_t> bad_addresses;
    bool align_bad_address(uint32_t &addr);

};

} // namespace FSPM

#endif // ADDRESS_PARSER_HPP
