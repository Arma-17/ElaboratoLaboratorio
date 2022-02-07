cmake_minimum_required(VERSION 3.20)
project(ElaboratoLaboratorio)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElaboratoLaboratorio
        main.cpp User.cpp  User.h Transaction.cpp Transaction.h Interface.cpp Interface.h BankAccount.cpp BankAccount.h)
