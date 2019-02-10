//
// Created by junichi on 19/01/23.
//

#include "node.h"
#include "../util.h"

/**
 * Node class constructor for type is not number.
 * @param _type
 * @param _lhs
 * @param _rhs
 */
Node::Node(int64_t _type, std::unique_ptr<Node> _lhs, std::unique_ptr<Node> _rhs) {
    type = _type;
    lhs = std::move(_lhs);
    rhs = std::move(_rhs);
}

/**
 * Node class constructor for number.
 * @param _val
 * @return
 */
Node::Node(int64_t _val) {
    type = NodeType_Number;
    val = _val;
}

/**
 * return token value that selected index
 * @param tokens
 * @param token_index
 * @return
 */
std::unique_ptr<Node>
Node::number(std::deque<std::unique_ptr<Token>> &tokens) {
    auto p = std::move(tokens.front());
    tokens.pop_front();
    if (p->type == TK_Number) {
        return std::make_unique<Node>(p->value);
    }
    error("number expected, but got ", p->input);
    return nullptr;
}

std::unique_ptr<Node>
Node::make_tree(std::deque<std::unique_ptr<Token>> &tokens) {
// change tokens to nodes
    auto lhs = number(tokens);
    std::unique_ptr<Token> p;
    for (;;) {
        p = std::move(tokens.front());
        if (p->type != '+' && p->type != '-') {
            break;
        }
        tokens.pop_front();
        lhs = std::make_unique<Node>(p->value, std::move(lhs), number(tokens));
    }

//    auto p = std::move(tokens.front());
    if (p->type != TK_EndMaker) {
        error("stray token: %s", p->input);
    }
    return lhs;
}

