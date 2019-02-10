cmake_minimum_required(VERSION 3.12)
project(occ)

set(CMAKE_CXX_STANDARD 17)

# add include for x64_86
#include_directories("hal_asm/intel")


add_executable(occ main.cpp encode/encode.cpp encode/encode.h IntermediateRepresentation/IntermediateRepresentation.cpp IntermediateRepresentation/IntermediateRepresentation.h node/node.cpp node/node.h util.cpp util.h token/token.cpp token/token.h hal_asm/intel/x86.cpp hal_asm/intel/x86.h)


