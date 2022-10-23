//
// Created by arman on 10/03/2022.
//

#include <gtest/gtest.h>
#include "../Transaction.h"

class TransactionTest: public ::testing::Test{
public:
    std::unique_ptr<std::tm> createDate(){
        std::unique_ptr<std::tm> date=std::make_unique<tm>();
        date->tm_year=100;
        date->tm_mon=1;
        date->tm_mday=2;
        date->tm_hour=10;
        date->tm_min=20;
        date->tm_sec=30;
        return date;
    }

};


TEST_F(TransactionTest,TransactionTimeSetTest){
    std::unique_ptr<std::tm> date=createDate();
    std::unique_ptr<Transaction> transactionTest=std::make_unique<Transaction>(0,DEPOSIT,"testUser","testCause",date.get());
    ASSERT_EQ(std::asctime(date.get()),transactionTest->getDateAndTime());
}
