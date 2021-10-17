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

