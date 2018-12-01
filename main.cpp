#include <iostream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

// Token Number class
enum class TokenNumber{
    Number = 256,
    plus,
    minus,
    EndOfFile
};

class Token{
private:

public:
    Token(TokenNumber _type, int _value, char * _input){
        type = _type;
        value = _value;
        input = _input;
    }
    TokenNumber  type;
    int value;
    char *input;
};



/**
 * error reporting funtion
 * @param i
 */
void fail(char *input) {
    cerr << "unexpected token: " << input << endl;
    exit(1);
}


// token and input is stored to this array.
vector<Token *> tokens;

void tokenize(char *p){
    int i = 0;
    while(*p){
        // skip white space
        if(isspace(*p)){
            p++;
            continue;
        }

        // + or -
        if(*p == '+'){
            tokens.push_back(new Token(TokenNumber ::plus, null, p));
            p++;
            continue;
        }
        if(*p == '-'){
            tokens.push_back(new Token(TokenNumber ::minus, null, p));
            p++;
            continue;
        }

        // Number
        if(isdigit(*p)){
            tokens.push_back(new Token(TokenNumber ::Number, strtol(p, &p, 10), p));
            p++;
            continue;
        }

        cerr << "cannot tokenize ..[" << p << "]" << endl;
        exit(1);
    }
    tokens.push_back(new Token(TokenNumber::EndOfFile, null, null));
}

int main(int argc,  char *argv[]) {
    if(argc != 2){
        cerr << "Usage : occ <code>" << endl;
    }

    tokenize(argv[1]);
    cout << ".intel_syntax noprefix" << endl;
    cout << ".global main" << endl;
    cout << "main:" << endl;

    // check the first token is Number.
    if(tokens[0]->type != TokenNumber::Number) {
       fail(tokens[0]->input);
    }

    cout << "  mov rax, " << tokens[0]->value << endl;

    int index = 1;
    while (tokens[index]->type != TokenNumber::EndOfFile) {
        if (tokens[index]->type == TokenNumber::plus) {
            index++;
            if (tokens[index]->type != TokenNumber::Number) {
                fail(tokens[index]->input);
            }
            cout << " add rax, " << tokens[index]->value << endl;
            index++;
            continue;
        }
        if (tokens[index]->type == TokenNumber::minus) {
            index++;
            if (tokens[index]->type != TokenNumber::Number) {
                fail(tokens[index]->input);
            }
            cout << " sub rax, " << tokens[index]->value << endl;
            index++;
            continue;
        }
        fail(tokens[index]->input);
    }
    cout << "  ret" << endl;
    return 0;
}