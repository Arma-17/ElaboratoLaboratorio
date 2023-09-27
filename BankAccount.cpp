//
// Created by arman on 02/10/2021.
//

#include "BankAccount.h"




//basic account operation
Transaction BankAccount::removeTransaction(int index, int type) {

    std::unique_ptr<Transaction> tmp;

    if (type == WITHDRAW) {
        if (index >= 1 && index <= transactionHistoryWithdraw.size()) {
            tmp.swap(transactionHistoryWithdraw.at(index - 1));
            transactionHistoryWithdraw.erase(transactionHistoryWithdraw.begin() + index - 1);
        } else {
            throw std::runtime_error("Error: Withdraw transaction index out of bounds or transaction doesn't exist.");
        }
    } else if (type == DEPOSIT) {
        if (index >= 1 && index <= transactionHistoryDeposit.size()) {
            tmp.swap(transactionHistoryDeposit.at(index - 1));
            transactionHistoryDeposit.erase(transactionHistoryDeposit.begin() + index - 1);
        }  else {
            throw std::runtime_error("Error: Deposit transaction index out of bounds or transaction doesn't exist.");
        }
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



std::vector<Transaction> BankAccount::getWithdrawTransactions() const {
    std::vector<Transaction> withdrawTransactions;

    for (const auto& transaction : transactionHistoryWithdraw) {
        withdrawTransactions.push_back(*transaction);
    }

    return withdrawTransactions;
}

//transaction search operations
std::vector<Transaction> BankAccount::searchTransactionsByCause(const std::string& cause) const {
    std::vector<Transaction> matchingTransactions;

    for (const auto& deposit : transactionHistoryDeposit) {
        if (deposit->getCause().find(cause) != std::string::npos) {
            matchingTransactions.push_back(*deposit);
        }
    }
    for (const auto& withdraw : transactionHistoryWithdraw) {
        if (withdraw->getCause().find(cause) != std::string::npos) {
            matchingTransactions.push_back(*withdraw);
        }
    }

    return matchingTransactions;
}

std::vector<Transaction> BankAccount::searchTransactionsBySender(const std::string& sender) const {
    std::vector<Transaction> matchingTransactions;

    for (const auto& deposit : transactionHistoryDeposit) {
        if (deposit->getSender().find(sender) != std::string::npos) {
            matchingTransactions.push_back(*deposit);
        }
    }
    for (const auto& withdraw : transactionHistoryWithdraw) {
        if (withdraw->getSender().find(sender) != std::string::npos) {
            matchingTransactions.push_back(*withdraw);
        }
    }

    return matchingTransactions;
}

std::vector<Transaction> BankAccount::searchTransactionsByDate(const std::string& date) const {
    std::vector<Transaction> matchingTransactions;

    for (const auto& deposit : transactionHistoryDeposit) {
        if (deposit->getDateAndTime().find(date) != std::string::npos) {
            matchingTransactions.push_back(*deposit);
        }
    }
    for (const auto& withdraw : transactionHistoryWithdraw) {
        if (withdraw->getDateAndTime().find(date) != std::string::npos) {
            matchingTransactions.push_back(*withdraw);
        }
    }

    return matchingTransactions;
}