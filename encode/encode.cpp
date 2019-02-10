//
// Created by junichi on 19/01/23.
//

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include "encode.h"


/**
 * remove what is not ascii.
 * @param _code  std::string source code
 * @return std::string source code as ascii
 */
std::string get_ascii_code(std::string _code) {
    int char_size;
    std::vector<std::string> v;

    for (int pos = 0; pos < _code.size(); pos += char_size) {
        // == take out 1 character.   ====================
        unsigned char lead = _code[pos];
        if (lead < 0x80) {
            char_size = 1;
        } else if (lead < 0xE0) {
            char_size = 2;
        } else if (lead < 0xF0) {
            char_size = 3;
        } else {
            char_size = 4;
        }
        if (char_size == 1) {             // take out only ascii code
            v.push_back(_code.substr(pos, char_size));
        }
    }
    std::ostringstream os;
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(os));
    return os.str();
}
