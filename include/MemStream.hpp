/* Code adapted from http://stackoverflow.com/questions/7781898/get-an-istream-from-a-char */

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
    membuf(char* beg, char* end) {
        this->setg(beg, beg, end);
    }
};

#endif // MEM_STREAM_HPP
