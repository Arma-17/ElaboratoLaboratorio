//
// Created by arman on 02/10/2021.
//


#ifndef ELABORATOLABORATORIO_INTERFACE_H
#define ELABORATOLABORATORIO_INTERFACE_H
#include "User.h"
#include <limits>


class Interface {


public:

    //start program
    bool startProgram();

    //create a user profile and a bank account
    void createBankAccount();
    void createProfile();

    //print the various option the user has
    void printOptions();

    //input checks
     bool getStringInput ( std:: string & input, int minLength = 0, int maxLength = 100) const  ;
     bool getIntInput ( int &input, int maxVal = 100000000, int minVal = 0) const ;
    static void clear ();
    bool isValidDate (const tm *toCheck) const;


private:
    std::unique_ptr<User> user;
};


#endif //ELABORATOLABORATORIO_INTERFACE_H
