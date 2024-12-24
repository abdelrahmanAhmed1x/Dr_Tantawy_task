cmake_minimum_required(VERSION 3.29)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)
include_directories(/usr/include/eigen3)
add_executable(Calculator main.cpp
        expression.h
        expression.cpp
        differentation.h
        BaseConverter.h
        linearAlgebra.h
)
