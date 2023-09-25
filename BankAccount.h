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
    Transaction getWithdrawAtIndex(int index) const{
        return *transactionHistoryWithdraw.at(index);
    }
    size_t getSizeOfWithdraw() const{
        return transactionHistoryWithdraw.size();
    }
    Transaction getDepositAtIndex(int index) const{
        return *transactionHistoryDeposit.at(index);
    }
    size_t getSizeOfDeposit() const{
        return transactionHistoryDeposit.size();
    }

    //test
    std::vector<Transaction> getWithdrawTransactions() const;

    //transaction Search
    std::vector<Transaction> searchTransactionsByCause(const std::string &cause) const;
    std::vector<Transaction> searchTransactionsByDate(const std::string &date) const;
    std::vector<Transaction> searchTransactionsBySender(const std::string &Sender) const;

private:
    std::string accountName;
    int balance;
    std::vector<std::unique_ptr<Transaction>> transactionHistoryWithdraw;
    std::vector<std::unique_ptr<Transaction>> transactionHistoryDeposit;

};


#endif //ELABORATOLABORATORIO_BANKACCOUNT_H
