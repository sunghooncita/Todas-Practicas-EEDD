cmake_minimum_required(VERSION 3.29)
project(pr2cclm)

set(CMAKE_CXX_STANDARD 20)

add_executable(pr2cclm main.cpp
        Coche.cpp
        Coche.h
        VDinamico.h)
