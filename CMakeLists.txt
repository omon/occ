cmake_minimum_required(VERSION 3.12)
project(occ)

set(CMAKE_CXX_STANDARD 17)

# add include for x64_86
include_directories("hal_asm/intel")


add_executable(occ main.cpp)


