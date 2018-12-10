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
#include <assert.h>


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
    Token(TokenNumber _type, int _value, std::string _input) {
        type = _type;
        value = _value;
        input = _input;
    }

    TokenNumber type;
    int value;
    string input;
};

template <typename First>
void error(const First &first) {
    std:
    cerr << first << std::endl;
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


// token and input is stored to this array.
vector<unique_ptr<Token>> tokens;

static bool is_number_character(std::string character) {
    return character[0] >= 0x30 && character[0] <= 0x39;
}


/**
 * remove what is not ascii.
 * @param _code  std::string source code
 * @return std::string source code as ascii
 */
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


int pos = 0;

class Node {

public:
    TokenNumber type;       // node type
    struct Node *left_hand_side;
    struct Node *right_hand_side;
    int value;

    Node(int v) {
        type = TokenNumber ::Number;
        value = v;
    }

    Node(TokenNumber _type, int v, Node *left, Node *right) {
        type = _type;
        value = v;
        left_hand_side = left;
        right_hand_side = right;
    }
private:

};

Node *number() {
    if (tokens[pos]->type == TokenNumber::Number) {
        return new Node(tokens[pos++]->value);
    }
}

Node *expr() {
    Node *left_hand_side = number();
    for (;;) {
        TokenNumber op = tokens[pos]->type;
        if (op != TokenNumber::plus && op != TokenNumber::minus) {
            break;
        }
        pos++;
        left_hand_side = new Node(op, tokens[pos]->value, left_hand_side, number());
    }
    if (tokens[pos]->type != TokenNumber::EndOfFile) {
        error("stray token: ", tokens[pos]->input);
    }
    return left_hand_side;
}

// code generator
static const vector<string> regs = {"rdi", "rsi", "r10", "r11", "r12", "r13", "r14", "r15", ""};
int cur;


/**
 * generate assembly code
 * @param node generate node.
 * @return
 */
static std::string generate(Node *node) {
    if (node->type == TokenNumber::Number) {
        std::string reg = regs[cur++];
        if (reg == "") {
            error("register exhausted.");
        }
        cout << hal_asm_mov(reg, to_string(node->value)) << endl;
        return reg;
    }
    string dst = generate(node->left_hand_side);
    string src = generate(node->right_hand_side);

    if (node->type == TokenNumber::plus) {
        cout << hal_asm_add(dst, src) << endl;
        return dst;
    } else if (node->type == TokenNumber::minus) {
        cout << hal_asm_sub(dst, src) << endl;
        return dst;
    } else {
        assert(0 && "unknown oprator.");
    }
}


/**
 * tokenize function
 * @param _code input source code.
 */
static void tokenize(std::string _code) {
    char *code = const_cast<char *>(get_ascii_code(_code).c_str());  // get ascii char from source code.
    while (*code) {
        if (isspace(*code)) {  // ignore space
            code++;
        } else if (*code == '+') {      // add token plus
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::plus, 0, code)));
            code++;
        } else if (*code == '-') {      // add token minus
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::minus, 0, code)));
            code++;
        } else if (isdigit(*code)) {           // add token Number
            char *store = code;
            int i = strtol(code, &code, 10);
            tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::Number, i, store)));
        } else {            // error code
            cerr << "cannot tokenize ..[" << *code << "]" << endl;
            exit(1);
        }
    }
    tokens.push_back(unique_ptr<Token>(new Token(TokenNumber::EndOfFile, 0, code)));        // add token end of file
}

/**
 * occ main function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage : occ <code>" << endl;
        exit(1);
    }
    // argument to vector<string>
    vector<string> args(argv, argv + argc);

    tokenize(args[1]);      //  tokenize source code.
    Node *node = expr();

    cout << hal_asm_initial_1() << endl;
    cout << hal_asm_gobal_main() << endl;
    cout << hal_asm_main_function() << endl;

    cout << hal_asm_mov_rax(generate(node)) << endl;

    cout << hal_asm_return() << endl;
    return 0;
}