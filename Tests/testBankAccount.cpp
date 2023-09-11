//
// Created by arman on 10/03/2022.
//

#include <gtest/gtest.h>
#include "../BankAccount.h"

class BankAccountTest : public ::testing::Test {
public:
    std:: unique_ptr<BankAccount> tested;
    BankAccountTest(){
        tested = std::make_unique<BankAccount>("test");
    }
    std:: unique_ptr<std:: tm> createDate (){
        std:: unique_ptr <std:: tm> date = std::make_unique<tm>();
        date->tm_year = 100;
        date-> tm_mon = 1;
        date -> tm_mday = 1;
        date -> tm_hour = 10;
        date -> tm_min = 10;
        date -> tm_sec = 10;
        return date;
    }
};

TEST_F(BankAccountTest, depositTest){
    EXPECT_EQ (0,tested->getBalance()); //verify initial balance
    tested ->deposit("test",100, "test cause");
    ASSERT_EQ(100, tested-> getBalance());
}

TEST_F(BankAccountTest, withdrawTest){
    EXPECT_EQ (0,tested->getBalance()); //verify initial balance
    tested ->deposit("test",100, "test cause");
    tested ->withdraw("test",100, "test cause");
    ASSERT_EQ(0, tested-> getBalance());
}

TEST_F (BankAccountTest, withdrawInvalidTest){ //checks if the withdrawal is activated even with insufficient balance
    bool caught = false;
    tested ->deposit( "test",100, "test cause");
    try{
        tested->withdraw( "test",101, "test cause");
    }
    catch (std:: runtime_error & e) {
        caught = true;
    }
    ASSERT_TRUE(caught);
}



TEST_F (BankAccountTest, withdrawReturnTrue){ //checks if there is a return value in the case of a successful withdrawal
    tested ->deposit("test", 100, "test cause");
    ASSERT_EQ(true, tested -> withdraw ("test", 100, "test cause"));
}


TEST_F (BankAccountTest, depositTransactionHistoryTest){ //checks if deposit transaction history works
    tested ->deposit("test", 100, "test cause");
    //creates a transaction that shall be equal to the one in the last slot of the vector
    Transaction mustBeEqual (100,DEPOSIT,"test cause" , "test");
    ASSERT_EQ(mustBeEqual , (tested->getDepositAtIndex(tested->getSizeOfDeposit()-1) ));
}

TEST_F (BankAccountTest, withdrawTransactionHistoryTest){ //checks if withdraw transaction history works
    tested ->deposit("test", 100, "test cause");
    //creates a transaction that shall be equal to the one in the last slot of the vector
    Transaction mustBeEqual (100,WITHDRAW, "test cause", "test");
    tested->withdraw("test", 100, "test cause");
    ASSERT_EQ(mustBeEqual , (tested->getWithdrawAtIndex(tested->getSizeOfDeposit()-1) ));
}

TEST_F (BankAccountTest, addRemoveTransactionTest){ //checks if adding and removing transactions works
    std:: unique_ptr <std:: tm> dateAndTime = createDate();
    //creates a transaction that shall be equal to the one in the first slot of the vector
    Transaction num1 (100,WITHDRAW, "test cause", "test",dateAndTime.get()); //creates a transaction from the set date
    Transaction num2 (100,WITHDRAW, "test cause", "test"); //creates a transaction with local time so num1 and num2 are different
    //add the transactions
    tested->addTransaction(num1);
    tested->addTransaction(num2);
    //removes the last transaction
    tested->removeTransaction(2,WITHDRAW);
    std:: vector <Transaction> withdraw = tested ->getWithdrawTransactions();
    ASSERT_EQ(num1 , withdraw.at(withdraw.size()-1));
}


