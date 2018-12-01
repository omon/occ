#include <iostream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <memory>
#include <iterator>
#include "hal_asm_inline.h"


// Token Number class
enum class TokenNumber {
    Number = 256,
    plus,
    minus,
    EndOfFile
};

/**
 * Token class
 */
class Token {
private:

public:
    Token(TokenNumber _type, int _value, string _input) {
        type = _type;
        value = _value;
        input = _input;
    }

    TokenNumber type;
    int value;
    string input;
};


/**
 * error reporting funtion
 * @param i
 */
void fail(string input) {
    cerr << "unexpected token: " << input << endl;
    exit(1);
}


// token and input is stored to this array.
vector<unique_ptr<Token>> tokens;

static bool is_number_character(std::string character) {
    if (character[0] >= 0x30 && character[0] <= 0x39) {
        return true;
    } else {
        return false;
    }
}

static std::string get_ascii_code(std::string _code) {
    int char_size;
    vector<string> v;
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

vector<std::string> split(const string &s, char delim) {
    vector<string> elems;
    string item;
    for (char ch: s) {
        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}


static void tokenize(std::string _code) {
    char *code = const_cast<char *>(get_ascii_code(_code).c_str());

    while(*code){
        if (isspace(*code)) {
            code++;
        }else if (*code == '+') {
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::plus, 0, code)));
            code++;
        } else if (*code == '-') {
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::minus, 0, code)));
            code++;
        } else if (isdigit(*code)) {           // Number
            char *store = code;
            int i = strtol(code, &code, 10);
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::Number, i, store)));
        } else {
            cerr << "cannot tokenize ..[" << *code << "]" << endl;
            exit(1);
        }
    }
    tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::EndOfFile, 0, code)));
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage : occ <code>" << endl;
        exit(1);
    }
    // argument to vector<string>
    vector<string> args(argv, argv + argc);
    //cout << args.size() << endl;
    //for (auto v : args) {
    //    cout << v << endl;
    //}

    tokenize(args[1]);
    cout << hal_asm_initial_1() << endl;
    cout << hal_asm_gobal_main() << endl;
    cout << hal_asm_main_function() << endl;

    // check the first token is Number.
    if (tokens[0]->type != TokenNumber::Number) {
        fail(tokens[0]->input);
    }

    cout << hal_asm_mov(tokens[0]->value) << endl;

    int index = 1;
    while (tokens[index]->type != TokenNumber::EndOfFile) {
        if (tokens[index]->type == TokenNumber::plus) {
            index++;
            if (tokens[index]->type != TokenNumber::Number) {
                fail(tokens[index]->input);
            }

            cout << hal_asm_add(tokens[index]->value) << endl;
            index++;
            continue;
        }
        if (tokens[index]->type == TokenNumber::minus) {
            index++;
            if (tokens[index]->type != TokenNumber::Number) {
                fail(tokens[index]->input);
            }

            cout << hal_asm_sub(tokens[index]->value) << endl;
            index++;
            continue;
        }
        fail(tokens[index]->input);
    }
    cout << "  ret" << endl;
    return 0;
}