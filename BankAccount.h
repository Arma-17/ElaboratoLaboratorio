//
// Created by arman on 02/10/2021.
//

#ifndef ELABORATOLABORATORIO_BANKACCOUNT_H
#define ELABORATOLABORATORIO_BANKACCOUNT_H
#include <iostream>

class BankAccount {
private:
    std::string accountName;
    int balance;

public:
    explicit BankAccount(std::string n,int b=0):balance(b),accountName(n){};


    //basic operation
    void deposit(const std::string & profile,int value,const std::string & cause);
    void withdraw(const std::string & profile,int value,const std::string & cause);


};


#endif //ELABORATOLABORATORIO_BANKACCOUNT_H
