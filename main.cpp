#include <iostream>
#include <string>
#include <vector>
#include "encode/encode.h"
#include "token/token.h"
#include "node/node.h"
#include "IntermediateRepresentation/IntermediateRepresentation.h"
#include "hal_asm/intel/x86.h"



/**
 * @brief this is debug code for display node tree
 * @param node
 */
void print_tree(std::unique_ptr<Node> node){
    if(node->lhs != NULL){
        print_tree(std::move(node->lhs));
    }
    if(node->rhs != NULL){
        print_tree(std::move(node->rhs));
    }
    if(node->type == TK_Number){
        std::cout << node->val << std::endl;
    }else {
        std::cout << static_cast<char>(node->type) << std::endl;
        std::cout << "=================" << std::endl;
    }
}

/**
 * occ main function
* @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage : occ <code>" << std::endl;
        exit(1);
    }
    // argument to vector<string>
    std::vector<std::string> args(argv, argv + argc);

    // lexical analyzer
    auto tokens = Token::tokenize(args[1]);      //  tokenize source code.

    // syntax analyzer
    std::unique_ptr<Node> node = Node::make_tree(tokens);
//     check node (debug)
//     print_tree(std::move(node));

    // generate Intermediate representation code
    auto ir = std::make_unique<IntermediateRepresentation>();
    auto ir_code = ir->generate(std::move(node));


//  code generation
    auto generator = x86(std::move(ir_code));
    generator.generate("tmp.s");
    return 0;
}