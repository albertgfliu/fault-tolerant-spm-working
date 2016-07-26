#ifndef DATA_BIN_HPP
#define DATA_BIN_HPP

#include <stdint.h>

namespace FSPM {

typedef struct DataBin
{
    uint32_t start_address;
    uint32_t size;
} DataBin;

} // namespace FSPM


#endif
