//
// Created by junichi on 19/01/23.
//

#ifndef OCC_TOKEN_H
#define OCC_TOKEN_H

#include <memory>
#include <deque>
#include <string>


enum TokenType{
    TK_Number = 256,
    TK_EndMaker
};

/**
 * Token class
 */
class Token {
private:

public:
    Token(int64_t _type, int _value, char* _input);
    ~Token();

    int64_t type;
    int64_t value;
    char* input;

    static std::deque<std::unique_ptr<Token>> tokenize(std::string _code);
};




#endif //OCC_TOKEN_H
