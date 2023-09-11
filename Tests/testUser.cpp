//
// Created by arman on 10/03/2022.
//

#include <gtest/gtest.h>
#include "../User.h"


class UserTest: public ::testing::Test{
public:
    std::unique_ptr<User> test;
    std::tm * date;
    UserTest(){
        date= nullptr;
    }

    void SetUp () override {
        date = new std:: tm;
        date->tm_year = 100;
        date-> tm_mon = 1;
        date -> tm_mday = 1;
        date -> tm_hour = 10;
        date -> tm_min = 10;
        date -> tm_sec = 10;
        test = std::make_unique<User>("testName", "testSurname", date, "testAddress");
    }
};


TEST_F(UserTest,activeAccountTest){
    int active=test->getActiveAccount();
    ASSERT_EQ(0,active);
}

TEST_F(UserTest,addingAccountTest){
    test->addAccount("addAccountTest");
    ASSERT_EQ(test->getAccount().size(),1);
}

TEST_F(UserTest,transferAmountToAccountTest){
    test->addAccount("accountTest1");
    test->addAccount("accountTest2");
    test->getAccount().at(0)->deposit("depositTest",100,"causeTest");
    test->transfer(2,100,"transferTest");
    ASSERT_EQ(0,test->getAccount().at(0)->getBalance());
    ASSERT_EQ(100,test->getAccount().at(1)->getBalance());
}

TEST_F(UserTest,transferInvalidAmountToAccountTest){ //check if with an invalid amount the transfer fails
    test->addAccount("accountTest1");
    test->addAccount("accountTest2");
    test->getAccount().at(0)->deposit("depositTest",100,"causeTest");
    test->transfer(2,101,"transferTest");
    ASSERT_EQ(100,test->getAccount().at(0)->getBalance());
    ASSERT_EQ(0,test->getAccount().at(1)->getBalance());
}

TEST_F(UserTest, transferValidReturnTest){ //checks if transfer return true on a success
    test->addAccount("accountTest1");
    test->addAccount("accountTest2");
    test->getAccount().at(0)->deposit("depositTest",100,"causeTest");
    bool result = test->transfer(1,100,"transfer");
    ASSERT_TRUE(result);
}

TEST_F(UserTest, transferInvalidReturnTest){ //checks if transfer return false on a failure
    test->addAccount("accountTest1");
    test->addAccount("accountTest2");
    test->getAccount().at(0)->deposit("depositTest",100,"causeTest");
    bool result = test->transfer(1,101,"transfer");
    ASSERT_FALSE(result);
}



