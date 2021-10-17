//
// Created by arman on 02/10/2021.
//

#include "User.h"
User::~User(){
    saveInFile();
    readInFile();
    delete birthday;
}

bool User::withdraw(int value, const std::string &cause) {
    try{
        account.at(activeAccount)->withdraw(name+surname,value,cause);
    }
    catch (std::runtime_error& error){
        std::cout<<error.what()<<std::endl;
        return false;
    }
    return true;
}

void User::deposit(int value, const std::string &cause) {
    account.at(activeAccount)->deposit(name+surname,value,cause);
}


//information

void User::printUserInfo() const {
    std::cout<<"User Information : "<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Surname: "<<surname<<std::endl;
    std::cout<<"Birthday: "<<birthday->tm_mday<<"/"<<birthday->tm_mon<<"/"<<birthday->tm_year<<std::endl;
    std::cout<<"Address: "<<address<<std::endl;
}

void User::printAccountInfo() const {
    int i=1;
    for( const auto &itr:account){
        std::cout<<i<<") "<<itr->getName()<<" - "<<itr->getBalance()<<"$"<<std::endl;
        i++;
    }
}


// txt file operation


void User::saveInFile() const {
    std::ofstream data("data.txt");

    data<<" Details: "<<std::endl;
    data<<"Name: "<<name<<std::endl;
    data<<"Surname: "<<surname<<std::endl;
    data<<"Birthday: "<<birthday->tm_mday<<"/"<<birthday->tm_mon<<"/"<<birthday->tm_year<<std::endl;
    data<<"Address: "<<address<<std::endl;

    int i=1;
    for(const auto &itr:account){
        data << "Account n:"<<i<<"   "<< account.at(i-1)->getName()<<std::endl;
        data<< " Balance: "<< account.at(i-1)->getBalance()<<"$"<<std::endl;
    }
}

void User::readInFile() const {
    std::ifstream a("data.txt");
    if(a.is_open())
        std::cout<<a.rdbuf()<<std::endl;
}


