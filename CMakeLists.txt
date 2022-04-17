cmake_minimum_required(VERSION 3.20)
project(Max3Sat_TEP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Max3Sat_TEP main.cpp Timer.cpp Timer.h Problem.cpp Problem.h Clause.cpp Clause.h Optimizer.cpp Optimizer.h)
