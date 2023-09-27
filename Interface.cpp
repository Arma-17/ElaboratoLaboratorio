//
// Created by arman on 02/10/2021.
//


#include "Interface.h"

bool Interface::startProgram() {
    int input=0;
    if (!user){
        std:: cout << "Welcome, to make any action you first need to create a user profile"<< std:: endl;
        std:: cout << "Press (1) to create a user profile" << std:: endl ;
        std:: cout << "Press (0) to exit" << std:: endl;

        while (!getIntInput(input, 2)){}
            if (input == 0) {
                std::cout << " Closing... " << std::endl;
                return false;

            } else if (input == 1)
                createProfile();
    }
    if(user->getAccount().empty()){
        std:: cout << "To make any action you first need to create a bank account"<< std:: endl;
        std:: cout << "Press (1) to create an account" << std:: endl ;
        std:: cout << "Press (0) to exit" << std:: endl;
        while(!getIntInput(input,2)){}

            if (input == 0) {
                std::cout << " Closing... " << std::endl;
                return false;

            } else if (input == 1)
                createBankAccount();


    }
    printOptions();
    while(!getIntInput(input,7));
    switch (input) {
        case 1:{    //Deposit
            std::cout<<"Chose the amount you want to deposit, press (0) to cancel operation "<<std::endl;
            while(!getIntInput(input));
            if(input>0){
                std::cout<<" Please insert the cause of the operation: "<<std::endl;
                std::string cause;
                while (!getStringInput(cause));
                user->deposit(input,cause);
                std::cout<< " You have successfully deposited "<< input<< "$"<<std::endl;
            }
            break;
        }
        case 2:{    //Withdraw
            if(user->getAccount().at(user->getActiveAccount())->getBalance()>0){
                std::cout<<"Chose the amount you want to withdraw, press (0) to cancel operation "<<std::endl;
                while (!getIntInput(input,user->getAccount().at(user->getActiveAccount())->getBalance()));
                if(input>0){
                    std::cout<<" Please insert the cause of the operation: "<<std::endl;
                    std::string cause;
                    while (!getStringInput(cause));
                    user->withdraw(input,cause);
                    std::cout<< " You have successfully withdrawn "<< input<< "$"<<std::endl;
                }
                break;
            }
            else
                std:: cout << "Your balance is 0!" << std:: endl;
            break;
        }
        case 3:{    //transfer cash
            if (user -> getAccount().at (user->getActiveAccount())->getBalance() > 0){
                if (user -> getAccount().size() > 1){
                    int dest;
                    std::cout<<" These are your accounts : "<<std::endl;
                    user->printAccountInfo();
                    std:: cout << "Choose the destination account: ";
                    do {
                        while (!(getIntInput(dest)));
                        if (dest - 1 == user->getActiveAccount())
                            std:: cout << "Destination and source cannot be the same account, please select a valid account"<< std:: endl;
                    }
                    while (dest - 1 == user ->getActiveAccount() );

                    std:: cout << "Choose the amount you want to transfer, press (0) to cancel operation" << std:: endl;
                    std:: string cause;
                    do{
                        while (!(getIntInput(input)));
                        std:: cout << "Please insert a cause for your operation: "<< std:: endl;
                        while (!getStringInput(cause));
                        if (input == 0)
                            break;
                    }while (!(user->transfer(dest,input,cause)));
                    if (input > 0)
                        std:: cout << "You Successfully Transferred " << input << "$" << " to " << user-> getAccount().at(dest - 1)->getName() <<std:: endl;
                }
                else{
                    std:: cout << "You only have 1 account, to transfer money create another account!" << std:: endl;
                }
            }
            else {
                std:: cout << "You can't transfer anything, your balance is 0!" << std:: endl;
            }
            break;
        }
        case 4:{    //user details
            user->printUserInfo();
            break;
        }
        case 5:{    //account history
            std:: cout << "WITHDRAWS:" << std:: endl;
            user->printWithdrawHistory();
            std:: cout << "DEPOSITS:" << std:: endl;
            user->printDepositHistory();
            std:: cout << std:: endl;
            break;
        }
        case 6:{    //activate account
            user->printAccountInfo();
            std:: cout << "Select the number of the account you want to set active, press (0) to cancel operation " << std:: endl;
            while (!(getIntInput(input,static_cast<int>(user->getAccount().size()) )));
            if (input != 0)
                user ->switchAccount(input);
            break;
        }
        case 7:{    //create another bank account
            createBankAccount();
            break;
        }
        case 0:{    //close
            std:: cout << "Quitting..." << std:: endl;
            return false;
        }
        default:{
            std:: cerr<< "Something went wrong (interface)" <<std:: endl;
            break;
        }
    }
    return true;
}



//Create a Bank Account

void Interface::createBankAccount() {
    std::cout<<" Enter a name for your account : "<<std::endl;
    std::string input;
    while (!getStringInput(input, 5, 30));
    user->addAccount(input);
}

void Interface::createProfile() {
    std::cout<<" Please enter your name: "<<std::endl;
    std::string inputName;
    while (!getStringInput(inputName, 5, 60));
    std::cout<<" Please enter your surname: "<<std::endl;
    std::string inputSurname;
    while (!getStringInput(inputSurname, 5, 60));
    std:: cout << "Please enter your home address: "<< std:: endl;
    std:: string address;
    while (!getStringInput(address, 5, 60));
    tm * dateOfBirth = new tm;
    int counter = 0;
    do {
        if (counter != 0)
            std:: cout << "Invalid Date, please try again" << std:: endl;
        int day;
        std:: cout << "Please enter your day of birth (number)" << std:: endl;
        while (!(getIntInput(day, 31, 1)));
        int month;
        std:: cout << "Please enter your month of birth (number)" << std:: endl;
        while (!(getIntInput(month, 12, 1)));
        int year;
        std:: cout << "Please enter your year of birth (number)" << std:: endl;
        while (!(getIntInput(year)));
        dateOfBirth->tm_mday = day;
        dateOfBirth -> tm_mon = month ;
        dateOfBirth -> tm_year = year;
        counter ++;
    }while (!isValidDate(dateOfBirth));
    user = std::make_unique<User>(inputName,inputSurname,dateOfBirth,address);
}


void Interface ::printOptions() {
    std:: cout << "Welcome to account N."<< user-> getActiveAccount() + 1;
    std:: cout << " - " << user->getAccount().at(user ->getActiveAccount())->getName();

    std:: cout << " - Your BALANCE: "<< user->getAccount().at(user ->getActiveAccount())->getBalance() << "$"<< std:: endl;
    std:: cout << "Press (0) to quit and view session log" << std:: endl;
    std:: cout << "Press (1) to deposit cash" << std:: endl;
    std:: cout << "Press (2) to withdraw cash" << std:: endl;
    std:: cout << "Press (3) to transfer cash to a different account" << std:: endl;
    std:: cout << "Press (4) to check your User information" << std:: endl;
    std:: cout << "Press (5) to check your account transactions history " << std:: endl;
    std:: cout << "Press (6) to change active account" << std:: endl;
    std:: cout << "Press (7) to create another bank account" << std:: endl;

}





//FUNCTIONS TO GET INPUT


bool Interface ::getStringInput( std::string &input, int minLength, int maxLength) const { //takes a string as input
    //performs various checks on that string, returns true if it passes, false otherwise
    try{
        std::cin>>input;
        if (input.length() > maxLength){
            throw std:: out_of_range("String is bigger than maximum required length (" + std::to_string(maxLength) + ") chars");
        }
        if (input.length() < minLength){
            throw std:: out_of_range("String is smaller than minimum required length (" + std::to_string(minLength) + ") chars");
        }
    }
    catch (const std:: out_of_range & e){
        std:: cout << e.what()<< std:: endl;
        return false;
    }
    return true;
}


bool Interface ::getIntInput( int &input, int maxVal, int minVal) const {//takes an int as input
    //performs various checks on the int, returns true if it passes, false otherwise
    try {
        std:: cin >> input;
        if (std:: cin.good()){
            if (input < minVal)
                throw std:: out_of_range ("Input is smaller than minimum accepted value (" + std::to_string(minVal) +")");
            if (input > maxVal)
                throw std:: out_of_range ("Input exceeds the maximum number (" + std::to_string(maxVal) +")");
            if (input == 0)
                return true;
        }
        else {
            throw std:: out_of_range ("Invalid input, please try again");
        }

    }
    catch (const std:: out_of_range &e){
        std:: cout << e.what() << std:: endl;
        clear(); //clears the buffer
        return false;
    }
    clear(); //clears the buffer
    return true;
}

void Interface ::clear() { //clears input buffer, used in getIntInput
    std:: cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



bool Interface::isValidDate(const tm *toCheck) const{ //checks if a date is valid
    if(1900 <= toCheck->tm_year && toCheck -> tm_year <= 2024)
    {
        int thirtyOneDaysM[7] = {0,2,4,6,7,9,11}; //31 days months
        for (int i : thirtyOneDaysM){
            if (toCheck->tm_mon-1 == i){
                if (toCheck -> tm_mday > 0 && toCheck -> tm_mday <=31)
                    return true;
            }
        }
        int thirtyDaysM[4] = {3,5,8,10}; //thirty days months
        for (int i : thirtyDaysM){
            if (toCheck->tm_mon-1 == i){
                if (toCheck -> tm_mday > 0 && toCheck -> tm_mday <=30)
                    return true;
            }
        }
        if(toCheck -> tm_mon-1 ==1) //february
        {
            if((toCheck-> tm_year%400==0 || (toCheck-> tm_year%100!=0 && toCheck-> tm_year%4==0)) && toCheck-> tm_mday>0 && toCheck-> tm_mday<=29)
                return true;
            else if(toCheck-> tm_mday>0 && toCheck-> tm_mday<=28)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
