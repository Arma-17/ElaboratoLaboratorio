cmake_minimum_required(VERSION 3.20)
project(ElaboratoLaboratorio)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-main)


include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)

add_executable(ElaboratoLaboratorio main.cpp User.cpp  User.h Transaction.h Interface.cpp Interface.h BankAccount.cpp BankAccount.h Tests/testBankAccount.cpp Tests/testTransaction.cpp Tests/testUser.cpp)
target_link_libraries(ElaboratoLaboratorio gtest gtest_main)

