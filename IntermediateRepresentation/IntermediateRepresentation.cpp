//
// Created by junichi on 19/01/23.
//

#include "../util.h"
#include "IntermediateRepresentation.h"
#include <cassert>

/**
 * generate Intermediate representation
 * @param node
 */

int64_t IntermediateRepresentation::generate_sub(std::unique_ptr<Node> node) {
    if (node->type == NodeType_Number) {
        int r = reg_no++;
        ins->push_back(std::move(
                std::make_unique<IntermediateRepresentation>(IR_Imm, r, node->val)));
        return r;
    }
    assert(node->type != '+' || node->type != '-');
    int64_t lhs = generate_sub(std::move(node->lhs));
    int64_t rhs = generate_sub(std::move(node->rhs));
    ins->push_back(std::move(std::make_unique<IntermediateRepresentation>(node->type, lhs, rhs)));
    ins->push_back(
            std::move(std::make_unique<IntermediateRepresentation>(IR_Kill, rhs, 0)));


    return lhs;
}

std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> IntermediateRepresentation::generate(std::unique_ptr<Node> node) {
    int64_t r = generate_sub(std::move(node));
    ins->push_back(std::move(std::make_unique<IntermediateRepresentation>(IR_Return, r, 0)));
    return std::move(ins);
}