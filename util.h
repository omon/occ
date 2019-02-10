//
// Created by junichi on 19/01/23.
//

#ifndef OCC_UTIL_H
#define OCC_UTIL_H

#include <iostream>

/**
 * error reporting funtion
 * @param i
 */
template <typename First>
void error(const First &first) {
    std:
    std::cerr << first << std::endl;
}

/**
 * error reporting funtion
 * @param i
 */
template<typename First, typename... Rest>
void error(const First &first, const Rest &... rest) {
    std::cerr << first << std::endl;
    error(rest...);
    exit(1);
}

#endif //OCC_UTIL_H
