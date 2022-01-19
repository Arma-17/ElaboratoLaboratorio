//
// Created by arman on 02/10/2021.
//

#ifndef ELABORATOLABORATORIO_USER_H
#define ELABORATOLABORATORIO_USER_H
#include <ctime>
#include <memory>
#include <vector>
#include "BankAccount.h"

class User {
private:
    std::string name;
    std::string surname;
    tm * birthday;
    std::string address;
    std::vector<std::unique_ptr<BankAccount>> account;
    int activeAccount;
public:
    User(std::string n,std::string s,tm* b,std::string a):name(std::move(n)),surname(std::move(s)),address(std::move(a)),birthday(b){
        activeAccount=0;
    }
    ~User();

    //basic operation
    bool withdraw(int value,const std::string & cause);
    void deposit(int value,const std::string & cause);

    //transaction management
    bool transfer(int receiver, int value, const std::string & cause);
    void addTransaction(const Transaction &add);
    bool delTransaction(int index,int type);

    //file management
    void saveInFile() const;
    void readInFile() const;


    //print information
    void printUserInfo () const;
    void printAccountInfo () const;

    void printWithdrawHistory() const;
    void printDepositHistory() const;

    //getter
    const std::vector <std::unique_ptr<BankAccount>> &getAccount() const{
        return account;
    }
    int getActiveAccount() const{
        return activeAccount;
    }

};


#endif //ELABORATOLABORATORIO_USER_H
