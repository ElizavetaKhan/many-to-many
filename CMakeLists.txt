cmake_minimum_required(VERSION 3.25)
project(8_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(8_lab
        main.cpp
        students.cpp
        students.h
        courses.cpp
        courses.h
        many_to_Many.cpp
        many_to_Many.h
        NodeSTRUCTS.h ../../Downloads/8_lab/students.h ../../Downloads/8_lab/students.h)
