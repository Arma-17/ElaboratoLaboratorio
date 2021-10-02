//
// Created by arman on 02/10/2021.
//

#include "User.h"
User::~User(){
    saveInFile();
    readInFile();
    delete birthday;
}

