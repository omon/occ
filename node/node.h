//
// Created by junichi on 19/01/23.
//

#ifndef OCC_NODE_H
#define OCC_NODE_H

#include <vector>
#include <deque>
#include "../token/token.h"

enum NodeType {
    NodeType_Number = 256,
};

class Node {
public:
    int type;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
    int64_t val;

    Node(int64_t _type, std::unique_ptr<Node> _lhs, std::unique_ptr<Node> _rhs);

    Node(int64_t _val);

    static std::unique_ptr<Node> number(std::deque<std::unique_ptr<Token>> &tokens);


    static std::unique_ptr<Node>
    make_tree(std::deque<std::unique_ptr<Token>> &tokens);
// change tokens to nodes

//    static std::unique_ptr<Node> number(std::vector<std::unique_ptr<Token>> tokens, const int token_index);
//    static std::unique_ptr<Node> expr();
};


#endif //OCC_NODE_H
