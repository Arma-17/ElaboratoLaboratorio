//
// Created by arman on 02/10/2021.
//


#include "Interface.h"

bool Interface::startProgram() {
    int count=0;
    if (!user){
        std:: cout << "Welcome, to make any action you first need to create a user profile"<< std:: endl;
        std:: cout << "Press (1) to create a user profile" << std:: endl ;
        std:: cout << "Press (0) to exit" << std:: endl;

        std::cin>>count;
        for (int i = 0; i < 3; i++) {

            if (count == 0) {
                std::cout << " Closing... " << std::endl;
                return false;

            } else if (count == 1) {
                createProfile();

            } else {
                std::cout<<" The key pressed is invalid "<< std::endl;
                std::cout<<" You have "<<3-i<<" attempts left "<< std::endl;

                std:: cout << "Press (1) to create a user profile" << std:: endl ;
                std:: cout << "Press (0) to exit" << std:: endl;
                std::cin>>count;
            }
        }
        std::cout << " Closing... " << std::endl;
        return false;
    }

    if(user->getAccount().empty()){
        count=0;
        std:: cout << "To make any action you first need to create a bank account"<< std:: endl;
        std:: cout << "Press (1) to create an account" << std:: endl ;
        std:: cout << "Press (0) to exit" << std:: endl;
        std::cin>>count;
        for (int i = 0; i < 3; i++) {

            if (count == 0) {
                std::cout << " Closing... " << std::endl;
                return false;

            } else if (count == 1) {
                createBankAccount();

            } else {
                std::cout<<" The key pressed is invalid "<< std::endl;
                std::cout<<" You have "<<3-i<<" attempts left "<< std::endl;

                std:: cout << "Press (1) to create an account" << std:: endl ;
                std:: cout << "Press (0) to exit" << std:: endl;
                std::cin>>count;
            }
        }
        std::cout << " Closing... " << std::endl;
        return false;

    }
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
        while (!(getIntInput(day, 31)));
        int month;
        std:: cout << "Please enter your month of birth (number)" << std:: endl;
        while (!(getIntInput(month, 12)));
        int year;
        std:: cout << "Please enter your year of birth (number)" << std:: endl;
        while (!(getIntInput(year)));
        dateOfBirth->tm_mday = day;
        dateOfBirth -> tm_mon = month -1;
        dateOfBirth -> tm_year = year;
        counter ++;
    }while (!isValidDate(dateOfBirth));
    user = std::make_unique<User>(inputName,inputSurname,dateOfBirth,address);
}








//FUNCTIONS TO GET INPUT

bool Interface ::getStringInput(std::string &input, int minLength, int maxLength) { //takes a string as input
    //performs various checks on that string, returns true if it passes, false otherwise
    try{
        std::getline(std:: cin,input);
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

bool Interface ::getIntInput(int &input, int maxVal, int minVal) {//takes an int as input
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


bool Interface::isValidDate(tm *toCheck) { //checks if a date is valid
    if(1900 <= toCheck->tm_year && toCheck -> tm_year <= 2100)
    {
        int thirtyOneDaysM[7] = {0,2,4,6,7,9,11}; //31 days months
        for (int i : thirtyOneDaysM){
            if (toCheck->tm_mon == i){
                if (toCheck -> tm_mday > 0 && toCheck -> tm_mday <=31)
                    return true;
            }
        }
        int thirtyDaysM[4] = {3,5,8,10}; //thirty days months
        for (int i : thirtyDaysM){
            if (toCheck->tm_mon == i){
                if (toCheck -> tm_mday > 0 && toCheck -> tm_mday <=30)
                    return true;
            }
        }
        if(toCheck -> tm_mon ==1) //february
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
