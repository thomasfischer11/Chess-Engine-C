cmake_minimum_required(VERSION 3.19)
project(Chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -std=c++14 -fopenmp -march=native")

add_executable(Chess main.cpp Figure.h Position.cpp Position.h Move.cpp Move.h)