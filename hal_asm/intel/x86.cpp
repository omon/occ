//
// Created by junichi on 19/02/03.
//

#include <iostream>
#include <fstream>
#include "x86.h"
#include <cassert>
#include "../../util.h"
#include "hal_asm_inline.h"


int64_t x86::alloc(int64_t ir_reg) {
    if (reg_map[ir_reg] != -1) {
        int r = reg_map[ir_reg];
        assert(used[r]);
        return r;
    }
    for (int i = 0; i < sizeof(regs) / sizeof(*regs); i++) {
        if (used[i]){
            continue;
        }
        used[i] = true;
        reg_map[ir_reg] = i;
        return i;
    }
    error("register exhausted");
    return -1;
}

/**
 * kill stored register map.
 * @param r index
 */
void x86::kill(int64_t r) {
    assert(used[r]);
    used[r] = false;
}

/**
 * default constructor
 * @param _ir Intermediate representation code
 */
x86::x86(std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> _ir) {
    // initialize register map
    for(int i=0; i < sizeof(reg_map) / sizeof(*reg_map); i++){
        reg_map[i] = -1;
    }
    ir = std::move(_ir);
    // allocate
    for (auto itr = ir->begin(); itr != ir->end(); itr++) {
        switch ((*itr)->oprand) {
            case IR_Imm:
                (*itr)->left_hand_side = alloc((*itr)->left_hand_side);
                break;
            case IR_Mov:
            case '+':
            case '-':
                (*itr)->left_hand_side = alloc((*itr)->left_hand_side);
                (*itr)->right_hand_side = alloc((*itr)->right_hand_side);
                break;
            case IR_Return:
                kill(reg_map[(*itr)->left_hand_side]);
                break;
            case IR_Kill:
                kill(reg_map[(*itr)->left_hand_side]);
                (*itr)->oprand = IR_Nop;
                break;
            default:
                assert(0 && "unknown operator");
        }
    }
}

/**
 * generate assembler code for x86
 * @param file_path assembler code file path
 */
void x86::generate(const std::string file_path) {
    std::ofstream a(file_path.c_str());
    a << hal_asm_initial_1() << std::endl;
    a << hal_asm_gobal_main() << std::endl;
    a << hal_asm_main_function() << std::endl;

    for (auto itr = ir->begin(); itr != ir->end(); ++itr) {
        switch ((*itr)->oprand) {
            case IR_Imm:
                a << hal_asm_mov(regs[(*itr)->left_hand_side], std::to_string((*itr)->right_hand_side)) << std::endl;
                break;
            case IR_Mov:
                a << hal_asm_mov(regs[(*itr)->left_hand_side], regs[(*itr)->right_hand_side]) << std::endl;
                break;
            case IR_Return:
                a <<hal_asm_mov_rax(regs[(*itr)->left_hand_side]) << std::endl;
                a << hal_asm_return() << std::endl;
                break;
            case '+':
                a << hal_asm_add(regs[(*itr)->left_hand_side], regs[(*itr)->right_hand_side]) << std::endl;
                break;
            case '-':a << hal_asm_sub(regs[(*itr)->left_hand_side], regs[(*itr)->right_hand_side]) << std::endl;
                break;
            case IR_Nop:
                break;
            default:
                assert(0 && "unknown operator");
        }
    }
}