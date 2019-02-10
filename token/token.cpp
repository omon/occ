//
// Created by junichi on 19/01/23.
//
#include <iostream>
#include <memory>
#include "../encode/encode.h"
#include "token.h"

/**
 * Token class constructor
 * @param _type = token type
 * @param _value
 * @param _input = input string
 */
Token::Token(int64_t _type, int _value, char *_ptr) {
    type = _type;
    value = _value;
    input = _ptr;
    if(type == TK_Number){
        std::cout << "create token object" << value << std::endl;
    }else{
        std::cout << "create token character object" << char(value) << std::endl;
    }
}
Token::~Token(){
    std::cout << "token object is delete." << std::endl;
}

/**
 * tokenize function
 * @param _code input source code.
 */
std::deque<std::unique_ptr<Token>> Token::tokenize(std::string _code) {
    auto __code = get_ascii_code(_code);
    std::cout << __code.length() << std::endl;
    char *code = new char[__code.length()];       // TODO fix raw pointer
    char *store_code = code;
    __code.copy(code, __code.length());
    //    auto code = const_cast<char *>(get_ascii_code(_code).c_str());  // get ascii char from source code.
    std::cout << "code is " << std::endl;
    std::cout << __code << std::endl;
    auto tokens = std::deque<std::unique_ptr<Token>>();

    while (*code) {
        if (isspace(*code)) {  // ignore space
            code++;
        } else if (*code == '+' || *code == '-') {      // add token plus or minus
            tokens.push_back(std::move((std::make_unique<Token>(*code, *code, code))));
            code++;
        } else if (isdigit(*code)) {           // add token Number
            auto i = static_cast<int>(strtol(code, &code, 10));        // convert Number string to integer
            auto p = std::make_unique<Token>(TK_Number, i, code);
            tokens.push_back(std::move(p));
        } else {            // error code
            std::cerr << "cannot tokenize ..[" << *code << "]" << std::endl;
            delete[] store_code;
            exit(1);
        }
    }
    tokens.push_back(std::move(std::make_unique<Token>(TK_EndMaker, 0, nullptr)));        // add token end of file
    delete[] store_code;
    return  tokens;
}
