//
// Created by arman on 02/10/2021.
//

#ifndef ELABORATOLABORATORIO_INTERFACE_H
#define ELABORATOLABORATORIO_INTERFACE_H
#include "User.h"

class Interface {
private:
    std::unique_ptr<User> user;

public:

    //start program
    bool startProgram();

    //create a user profile and a bank account
    void createBankAccount();
    void createProfile();

    //print the various option the user has
    void printOptions();


};


#endif //ELABORATOLABORATORIO_INTERFACE_H
