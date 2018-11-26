#include <iostream>

using namespace std;

int main(int argc,  char *argv[]) {
    if(argc != 2){
        cerr << "Usage : occ <code>" << endl;
    }
    cout << ".intel_syntax noprefix" << endl;
    cout << ".global main" << endl;
    cout << "main:" << endl;
    cout << "  mov rax, " << argv[1] << endl;
    cout << "  ret" << endl;
    return 0;
}