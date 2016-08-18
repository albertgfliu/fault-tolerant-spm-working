#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <optionparser.h>

enum
optionIndex {
    INPUT,
    OUTPUT,
    FAULTMAP,
    IMEMSIZE,
    DMEMSIZE,
    HELP
};

const
option::Descriptor usage[] = //FILL THESE IN
{
    {INPUT,                 //index, defined in your own option enum
     0,                     //type, defined in your own type enum
     "i",                   //shortopt
     "input",               //longopt
     option::Arg::Optional, //check_arg
     "--input, -i    This required option takes an input ELF file."
     },
    {OUTPUT,
     0,
     "o",
     "output",
     option::Arg::Optional,
     "--output, -o      This optional option outputs an ELF file. If not set, the output ELF file will be named \"output.ELF\" by default."  
     },
    {FAULTMAP,
     0,
     "f",
     "faultmap",
     option::Arg::Optional,
     "--faultmap, -f    This required option takes an input fault-map file to parse."
     },
    {IMEMSIZE,
     0,
     "c",
     "imemsize",
     option::Arg::Optional,
     "--imemsize, -c     This optional option takes the instruction memory's size beginning at offset 0x00000000. If not set, the default size is 0x1FFFFFFF" 
    },
    {DMEMSIZE,
     0,
     "d",
     "dmemsize",
     option::Arg::Optional,
     "--dmemsize, -d    This optional option takes the data memory's size beginning at offset 0x20000000. If not set, the default size is 0x1FFFFFFF"
    }
};

#endif
