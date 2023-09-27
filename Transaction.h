//
// Created by arman on 05/01/2022.
//


#ifndef ELABORATOLABORATORIO_TRANSACTION_H
#define ELABORATOLABORATORIO_TRANSACTION_H
#include <iostream>
#include <ctime>
#include <utility>

const int DEPOSIT=1;
const int WITHDRAW=2;

class Transaction {
public:
    Transaction(int a,int ty,std::string c,std::string s ):type(ty),cause(std::move(c)),
    sender(std::move(s)){
        if (a < 0) {
            throw std::invalid_argument("Amount cannot be negative");
        }
        amount = a;
        std::time_t t=std::time(nullptr);
        dateAndTime= ctime(&t);                     //assign the current time when used
    }

    //overloaded constructor to use a date as input
    Transaction(int a,int ty,std::string c,std::string s,std::tm *time):type(ty),cause(std::move(c)),sender(std::move(s)){
        if (a < 0) {
            throw std::invalid_argument("Amount cannot be negative");
        }
        amount = a;
        dateAndTime=std::asctime(time);
    }

    // Define the equality operator
    bool operator==(const Transaction& other) const {
        return amount == other.amount &&
               type == other.type &&
               cause == other.cause &&
               sender == other.sender &&
               dateAndTime == other.dateAndTime;
    }


    //getters
     int getAmount() const{
        return amount;
    };
     int getType() const{
         return type;
     };
     const std::string &getDateAndTime() const{
         return dateAndTime;
     };
     const std::string &getCause() const{
         return cause;
     };
     const std::string &getSender() const{
         return sender;
     };

private:
    int amount;
    int type;
    std::string dateAndTime;
    std::string cause;
    std::string sender;


};


#endif //ELABORATOLABORATORIO_TRANSACTION_H
