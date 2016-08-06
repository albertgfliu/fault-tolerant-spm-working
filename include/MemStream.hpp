/* Code adapted from http://stackoverflow.com/questions/7781898/get-an-istream-from-a-char and http://stackoverflow.com/questions/13059091/creating-an-input-stream-from-constant-memory */

/* Usage
     membuf sbuf(buffer, buffer + sizeof(buffer));
     std::istream in(&sbuf);
   'in' can then be manipulated like a standard istream
*/

#ifndef MEM_STREAM_HPP
#define MEM_STREAM_HPP

#include <iostream>
#include <istream>
#include <streambuf>
#include <string>

struct membuf : std::streambuf
{
    membuf(const char* beg, size_t size) {
        char *p = const_cast<char *>(beg);
        this->setg(p, p, p + size);
    }
};

#endif // MEM_STREAM_HPP
