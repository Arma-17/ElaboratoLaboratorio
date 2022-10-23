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
    Transaction(int a,int ty,std::string c,std::string s ):amount(a),type(ty),cause(std::move(c)),
    sender(std::move(s)){
        std::time_t t=std::time(nullptr);
        dateAndTime= ctime(&t);                     //assign the current time when used
    }

    //overloaded constructor to use a date as input
    Transaction(int a,int ty,std::string c,std::string s,std::tm *time):amount(a),type(ty),cause(std::move(c)),sender(std::move(s)){
        dateAndTime=std::asctime(time);
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