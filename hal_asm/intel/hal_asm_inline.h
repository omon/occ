//
// Created by junichi on 18/12/01.
//

#pragma once

#include <string>
//using namespace std;


static inline std::string hal_asm_initial_1(){
    return  ".intel_syntax noprefix";
}
static inline std::string hal_asm_gobal_main(){
    return  ".global main";
}
static inline std::string hal_asm_main_function(){
    return  "main:";
}

static inline std::string hal_asm_mov_rax(int d){
   return "  mov rax, " +  std::to_string(d);
}
static inline std::string hal_asm_mov_rax(std::string s){
   return "  mov rax, " +  s;
}

static inline std::string hal_asm_add_rax(int d){
   return "  add rax, " +  std::to_string(d);
}
static inline std::string hal_asm_sub_rax(int d){
   return "  sub rax, " +  std::to_string(d);
}
static inline std::string hal_asm_mov(std::string reg, std::string d){
    return  "  mov " + reg + ", " + d;
}
static inline std::string hal_asm_add(std::string reg, std::string d){
    return  "  add " + reg + ", " + d;
}
static inline std::string hal_asm_sub(std::string reg, std::string d){
    return  "  sub " + reg + ", " + d;
}

static inline std::string hal_asm_return(){
    return "  ret";
}
