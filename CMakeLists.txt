cmake_minimum_required(VERSION 3.08)
project(MyMatrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyMatrix matrix.hpp
        matrix_main.cpp)

add_executable(TestMyMatrix matrix.hpp
        test.cpp)
