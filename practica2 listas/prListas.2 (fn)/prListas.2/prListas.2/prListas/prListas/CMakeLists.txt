cmake_minimum_required(VERSION 3.29)
project(prListas)

set(CMAKE_CXX_STANDARD 20)

add_executable(prListas main.cpp
        ListaDEnlazada.h
        ReanelCar.cpp
        ReanelCar.h
        Usuario.cpp
        Usuario.h
        Coche.cpp
        Coche.h
        VDinamico.h)
