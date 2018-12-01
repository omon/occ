//
// Created by junichi on 18/12/01.
//

#pragma once

#include <string>
using namespace std;


static inline string hal_asm_initial_1(){
    return  ".intel_syntax noprefix";
}
static inline string hal_asm_gobal_main(){
    return  ".global main";
}
static inline string hal_asm_main_function(){
    return  "main:";
}

static inline string hal_asm_mov(int d){
   return "  mov rax, " +  to_string(d);
}
static inline string hal_asm_add(int d){
   return "  add rax, " +  to_string(d);
}
static inline string hal_asm_sub(int d){
   return "  sub rax, " +  to_string(d);
}
