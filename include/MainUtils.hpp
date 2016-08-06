#ifndef MAIN_UTILS_HPP
#define MAIN_UTILS_HPP

#include <string>
#include <elfio/elfio.hpp>

namespace ELFIO {

const
section *
getSectionByName(elfio &reader, std::string name)
{
    Elf_Half sec_num = reader.sections.size();

    for (int i = 0; i < sec_num; ++i) {
        const section *psec = reader.sections[i];
        if (name.compare(psec->get_name()) == 0) {
            return psec;
        }
    }
    return nullptr;
}

}

#endif // MAIN_UTILS_HPP
