cmake_minimum_required(VERSION 3.20)
project(ElaboratoLaboratorio)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElaboratoLaboratorio
        main.cpp User.h User.cpp Interface.h Interface.cpp BankAccount.h BankAccount.cpp)
