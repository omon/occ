//
// Created by junichi on 19/01/23.
//

#ifndef OCC_INTERMEDIATEREPRESENTATION_H
#define OCC_INTERMEDIATEREPRESENTATION_H


#include "../node/node.h"

enum IntermediateRepresentationType {
    IR_Imm,
    IR_Mov,
    IR_Return,
    IR_Kill,
    IR_Number,
    IR_Nop
};

/**
 * Intermediate representation class
 */
class IntermediateRepresentation {
private:
    std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> ins;
    int64_t  reg_no;
public:
    int64_t oprand;
    int64_t left_hand_side;
    int64_t right_hand_side;

    IntermediateRepresentation(){
        reg_no = 0;
        ins = std::make_unique<std::deque<std::unique_ptr<IntermediateRepresentation>>>();
    }
    IntermediateRepresentation(int op, int lhs, int rhs) {
        oprand = op;
        left_hand_side = lhs;
        right_hand_side = rhs;
    }

    std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> generate(std::unique_ptr<Node> node);
    int64_t generate_sub(std::unique_ptr<Node> node);

};

#endif //OCC_INTERMEDIATEREPRESENTATION_H
