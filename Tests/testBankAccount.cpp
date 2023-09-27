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


// Test for searching transactions by cause
TEST_F(BankAccountTest, searchTransactionsByCauseTest) {
    tested->deposit("test1", 100, "test cause 1");
    tested->deposit("test2", 200, "test cause 2");
    tested->deposit("test3", 150, "test cause 3");
    tested->withdraw("test4", 50, "test cause 4");

    std::vector<Transaction> result = tested->searchTransactionsByCause("cause 2");

    // Ensure that only transactions with "cause 2" are included in the result
    for (const auto& transaction : result) {
        ASSERT_EQ("test cause 2", transaction.getCause());
    }

    ASSERT_EQ(1, result.size());
}

// Test for searching transactions by sender
TEST_F(BankAccountTest, searchTransactionsBySenderTest) {
    tested->deposit("sender1", 100, "test cause 1");
    tested->deposit("sender2", 200, "test cause 2");
    tested->withdraw("sender3", 150, "test cause 3");
    tested->withdraw("sender4", 50, "test cause 4");

    std::vector<Transaction> result = tested->searchTransactionsBySender("sender2");

    for (const auto& transaction : result) {
        ASSERT_EQ("sender2", transaction.getSender());
    }

    ASSERT_EQ(1, result.size());
}

// Test for searching transactions by date
TEST_F(BankAccountTest, searchTransactionsByDateTest) {
    tested->deposit("test1", 100, "test cause 1");
    tested->deposit("test2", 200, "test cause 2");
    tested->deposit("test3", 150, "test cause 3");
    tested->withdraw("test4", 50, "test cause 4");

    // Use the current date as a search criterion
    std::time_t t = std::time(nullptr);
    std::string currentDate = ctime(&t);

    std::vector<Transaction> result = tested->searchTransactionsByDate(currentDate);

    for (const auto& transaction : result) {
        ASSERT_EQ(currentDate, transaction.getDateAndTime());
    }

    ASSERT_EQ(4, result.size());
}

TEST_F(BankAccountTest, removeNonExistentTransactionTest) {
    tested->deposit("test1", 100, "test cause 1");
    tested->deposit("test2", 200, "test cause 2");
    tested->deposit("test3", 150, "test cause 3");
    tested->withdraw("test4", 50, "test cause 4");

    int initialBalance = tested->getBalance();
    size_t initialWithdrawSize = tested->getSizeOfWithdraw();
    size_t initialDepositSize = tested->getSizeOfDeposit();

    try {
        tested->removeTransaction(2, WITHDRAW);
        FAIL() << "Expected an exception for removing a non-existent transaction.";
    } catch (const std::runtime_error& e) {
        SUCCEED();
    }
    // final check on the parameters
    ASSERT_EQ(initialBalance, tested->getBalance());
    ASSERT_EQ(initialWithdrawSize, tested->getSizeOfWithdraw());
    ASSERT_EQ(initialDepositSize, tested->getSizeOfDeposit());
}


