//
// Created by junichi on 19/02/03.
//

#ifndef OCC_X86_H
#define OCC_X86_H

#include <string>
#include "../../IntermediateRepresentation/IntermediateRepresentation.h"

/**
 * code generator for x86
 */
class x86 {
private:
    /**
     * register for x86
     */
    constexpr static const char *regs[] = {"rdi", "rsi", "r10", "r11", "r12", "r13", "r14", "r15"};
    /**
     * used register.
     */
    bool used[sizeof(regs) / sizeof(regs[0])];
    /**
     * register map
     */
//    std::unique_ptr<int64_t reg_map[1000];
    int64_t reg_map[1000];

    /**
     * allocate register map
     * @param ir_reg
     * @return
     */
    int64_t alloc(int64_t ir_reg);

    /**
     *
     * @param r
     */
    void kill(int64_t r);

    /**
     * stored Intermediate representation code
     */
    std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> ir;


public:
    /**
     * default constructor
     * @param _ir Intermediate representation code
     */
    x86(std::unique_ptr<std::deque<std::unique_ptr<IntermediateRepresentation>>> _ir);

    /**
    * generate assembler code for x86
    * @param file_path assembler code file path
    */
    void generate(const std::string file_path);
};


#endif //OCC_X86_H
