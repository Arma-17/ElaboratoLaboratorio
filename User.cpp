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

void User::printDepositHistory() const {
    if(account.at(activeAccount)->getSizeOfDeposit() != 0) {
        for (int i = 0; i < account.at(activeAccount)->getSizeOfDeposit(); i++) {
            auto iter = account.at(activeAccount)->getDepositAtIndex(i);
            std::cout << " In: " << iter.getDateAndTime() << ", " << iter.getSender();
            std::cout << "  Deposited : ";
            std::cout << iter.getAmount() << " $ " << std::endl;
            std::cout << " Cause : " << iter.getCause() << std::endl;
        }
    }
    else
        std::cout<<" No deposit has been made "<< std::endl;
}

void User::printWithdrawHistory() const {
    if(account.at(activeAccount)->getSizeOfWithdraw()!=0) {
        for (int i = 0; i < account.at(activeAccount)->getSizeOfWithdraw(); i++) {
            auto iter = account.at(activeAccount)->getWithdrawAtIndex(i);
            std::cout << " In: " << iter.getDateAndTime() << ", " << iter.getSender();
            std::cout << "  Withdrawn : ";
            std::cout << iter.getAmount() << " $ " << std::endl;
            std::cout << " Cause : " << iter.getCause() << std::endl;
        }
    }
    else
        std::cout<<" No withdrawal has been made " << std::endl;
}

//add bank Account
void User::addAccount(const std::string &accountName) {
    account.push_back(std::make_unique<BankAccount>(accountName));
}

void User::switchAccount(int accountNumber) { //switches active account
    activeAccount = accountNumber - 1;
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
        i++;
    }
}

void User::readInFile() const {
    std::ifstream a("data.txt");
    if(a.is_open())
        std::cout<<a.rdbuf()<<std::endl;
}



//transaction management
void User::addTransaction(const Transaction &add) {
    account.at(activeAccount)->addTransaction(add);
}

bool User::delTransaction(int index, int type) {
    try{
        account.at(activeAccount)->removeTransaction(index,type);
    }
    catch (std::out_of_range &error){
        std::cout<<error.what()<<std::endl;
        return false;
    }
    return true;
}


bool User::transfer(int dest, int value, const std::string &cause) {
    try{
        account.at(activeAccount)->withdraw(name+surname,value,cause);
    }
    catch (std:: runtime_error & e){
        std :: cout << e.what() << std:: endl;
        return false;
    }
    account.at(dest - 1)->deposit(name+surname,value,cause);
    return true;
}

const std::vector<std::unique_ptr<BankAccount>> &User::getAccount() const {
    return account;
}