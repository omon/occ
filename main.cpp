#include <iostream>

using namespace std;

int main(int argc,  char *argv[]) {
    if(argc != 2){
        cerr << "Usage : occ <code>" << endl;
    }
    cout << ".intel_syntax noprefix" << endl;
    cout << ".global main" << endl;
    cout << "main:" << endl;
    char * p = argv[1];
    //cout << "  mov rax, " << argv[1] << endl;
    cout << "mov rax, " << strol(p, &p, 10);

    while(*p){
        if(*p == '+'){
            p++;
            cout << " add rax, " << strol(p, &p, 10) << "\n";
            continue;
        }

        if(*p == '-'){
            p++;
            cout << " add rax, " << strol(p, &p, 10) << "\n";
            continue;
        }
        cerr << "unexpected character: " << *p << "\n";
        return 1;
    }
    cout << "  ret" << endl;
    return 0;
}