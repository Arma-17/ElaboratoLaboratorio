//
// Created by arman on 02/10/2021.
//

#ifndef ELABORATOLABORATORIO_BANKACCOUNT_H
#define ELABORATOLABORATORIO_BANKACCOUNT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Transaction.h"

class BankAccount {
private:
    std::string accountName;
    int balance;
    std::vector<std::unique_ptr<Transaction>> transactionHistoryWithdraw;
    std::vector<std::unique_ptr<Transaction>> transactionHistoryDeposit;


public:
    explicit BankAccount(std::string n,int b=0):balance(b),accountName(std::move(n)){};


    //basic operation
    void deposit(const std::string & profile,int value,const std::string & cause);
    bool withdraw(const std::string & profile,int value,const std::string & cause);
    void addTransaction(const Transaction& add);
    Transaction removeTransaction(int index,int type);


    //getter
    const std::string & getName() const{
        return accountName;
    }
    int getBalance() const {
        return balance;
    }
    const std::vector<std::unique_ptr<Transaction>> &Withdraw() const{
        return transactionHistoryWithdraw;
    }
    const std::vector<std::unique_ptr<Transaction>> &Deposit() const{
        return transactionHistoryDeposit;
    }
};


#endif //ELABORATOLABORATORIO_BANKACCOUNT_H
