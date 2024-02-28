#include "gtest/gtest.h"
#include "../include/SlotMachine.h"

TEST(SlotMachineTest, NewBalanceTest){
    SlotMachine* MyGame = new SlotMachine()
    MyGame->MakeBet(50);
    int newbalance;
    newbalance = MyGame->NewBalance();

    EXPECT_NE(newbalance, 5000);
}

//TEST(SlotMachineTest, NewBalanceTest2){
//    SlotMachine MyGame->SlotMachine(5000);
//    int newbalance;
//    newbalance = MyGame->NewBalance();
//
//    EXPECT_NE(newbalance, 10000);
//}   

TEST(SlotMachineTest, BetTest){
    SlotMachine* MyGame = new SlotMachine();
    MyGame->MakeBet(100);
    int betAmount;
    betAmount  = MyGame->getBet();

    EXPECT_EQ(betAmount,100);
}

TEST(SlotMachineTest, BetTest2){
    SlotMachine* MyGame = new SlotMachine();
    MyGame->MakeBet(200);
    int betAmount;
    betAmount =  MyGame->getBet();

    EXPECT_NE(betAmount,500);
}

//TEST(SlotMachineTest, GameTest){
//    SlotMachine MyGame->SlotMachine(500);
//    MyGame->MakeBet(50);
//    MyGame->SpinMachine();
//    
//    int UpdatedMoney;
//
//    UpdatedMoney = MyGame->NewBalance();
//
//    EXPECT_NEW(UpdatedMoney, 500);
//}

TEST(SlotMachineTest, GameTest1){
    EXPECT_NO_THROW(SlotMachine* Game = new SlotMachine());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}