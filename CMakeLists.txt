cmake_minimum_required(VERSION 3.27)
project(TAD_Dictionar_Ordonat)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(TAD_Dictionar_Ordonat
        "Proiect C++/App.cpp"
        "Proiect C++/DO.cpp"
        "Proiect C++/DO.h"
        "Proiect C++/Iterator.cpp"
        "Proiect C++/Iterator.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
