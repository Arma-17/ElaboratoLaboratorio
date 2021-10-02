//
// Created by arman on 02/10/2021.
//

#ifndef ELABORATOLABORATORIO_USER_H
#define ELABORATOLABORATORIO_USER_H
#include <iostram>
#include <ctime>
#include <memory>
#include <vector>
#include "BankAccount.h"

class User {
private:
    std::string name;
    std::string surname;
    tm * birthday;
    std::sting address;
    std::vector<std::unique_ptr<BankAccount>> account;
    bool activeAccount;
public:
    User(std::string n,std::sting s,tm* b,std::string a):name(n),surname(s),address(a),birthday(b){
        activeAccount=false;
    }
    ~User();

    //basic operation
    bool withdraw(int value,const std::string & cause);
    bool deposit(int value,const std::string & cause);

    //transaction management
    bool transfer(int receiver, int value, const std::string & cause);

    //file management
    void saveInFile() const;
    void readInFile() const;


    //print information
    void printUserInfo () const;
    void printAccountInfo () const;

    void printWithdrawHistory() const;
    void printDepositHistory() const;




};


#endif //ELABORATOLABORATORIO_USER_H
