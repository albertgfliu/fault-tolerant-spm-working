#ifndef F_ARG_H
#define F_ARG_H

#include <optionparser.h>

#include <cstdint>
#include <stdio.h>

/*
 * Adapted from https://github.com/nanocad-lab/X-Mem/blob/master/src/include/ExampleArg.h
 * and https://github.com/nanocad-lab/X-Mem/blob/master/src/include/MyArg.h
 */

class FArg : public option::Arg
{
    public:
        static void printError(const char* msg1, const Option& opt, const char* msg2) {
            fprintf(stderr, "ERROR: %s", msg1);
            fwrite(opt.name, opt.namelen, 1, stderr);
            fprintf(stderr, "%s", msg2);
        } 

        static ArgStatus Unknown(const Option& option, bool msg) {
            if (msg)
                printError("Unknown option '", option, "'\n");
            return ARG_ILLEGAL;
        }

        static ArgStatus Required(const Option& option, bool msg) {
            if (option.arg != 0)
                return ARG_OK;

            if (msg)
                printError("Option '", option, "' requires an argument\n");
            return ARG_ILLEGAL;
        }

        static ArgStatus NonEmpty(const Option& option, bool msg) {
            if (option.arg != 0 && option.arg[0] != 0)
                return ARG_OK;
        
            if (msg)
                printError("Option '", option, "' requires a non-empty argument\n");
            return ARG_ILLEGAL;
        }
        
        static ArgStatus Integer(const Option& option, bool msg) {
            char* endptr = 0;
            if (option.arg != 0 && strtol(option.arg, &endptr, 10)) {};
            if (endptr != option.arg && *endptr == 0)
                return ARG_OK;
            
            if (msg)
                printError("Option '", option, "' requires an integer argument\n");
            return ARG_ILLEGAL;
        }
        
        static ArgStatus NonnegativeInteger(const Option& option, bool msg) {
            char* endptr = 0;
            int32_t tmp = -1;
            if (option.arg != 0)
                tmp = strtol(option.arg, &endptr, 10);
            if (endptr != option.arg && *endptr == 0 && tmp >= 0)
                return ARG_OK;
            
            if (msg)
                printError("Option '", option, "' requires a non-negative integer argument\n");  
            return ARG_ILLEGAL;
        }

        static ArgStatus PositiveInteger(const Option& option, bool msg) {
            char* endptr = 0;
            int32_t tmp = -1;
            if (option.arg != 0)
                tmp = strtol(option.arg, &endptr, 10);
            if (endptr != option.arg && *endptr == 0 && tmp > 0)
               return ARG_OK;

            if (msg)
                printError("Option '", option, "' requires a positive integer argument\n");
            return ARG_ILLEGAL;
        }
};

#endif
