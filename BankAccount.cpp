//
// Created by arman on 02/10/2021.
//

#include "BankAccount.h"




//basic account operation
Transaction BankAccount::removeTransaction(int index,int type) {
    std::unique_ptr<Transaction> tmp;
    if (type==WITHDRAW){
        tmp.swap(transactionHistoryWithdraw.at(index-1));
        transactionHistoryWithdraw.erase(transactionHistoryWithdraw.begin()+index-1);
    }
    else if(type==DEPOSIT){
        tmp.swap(transactionHistoryDeposit.at(index-1));
        transactionHistoryDeposit.erase(transactionHistoryDeposit.begin()+index-1);
    }

    return *tmp;
}

void BankAccount::addTransaction(const Transaction &add) {
    if(add.getType()==WITHDRAW){
        transactionHistoryWithdraw.push_back(std::make_unique<Transaction>(add));
    }
    else if(add.getType()==DEPOSIT) {
        transactionHistoryDeposit.push_back(std::make_unique<Transaction>(add));
    }
}



bool BankAccount::withdraw(const std::string &profile, int value, const std::string &cause) {
    if(balance>= value){
        balance-=value;
        transactionHistoryWithdraw.push_back(std::make_unique<Transaction>(value,WITHDRAW,cause,profile));
        return true;
    }
    else{
        throw (std::runtime_error("Error, exceeding account balance, please input a valid amount"));
    }
}

void BankAccount::deposit(const std::string &profile, int value, const std::string &cause) {
    balance+=value;
    transactionHistoryDeposit.push_back(std::make_unique<Transaction>(value,DEPOSIT,cause,profile));
}

