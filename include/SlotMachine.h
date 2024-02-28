#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H
#include <iostream>

using namespace std;

class SlotMachine{
    private:

        int item1;
        int item2;
        int item3;
        int playercoins; 
        int bet;
    
    public:
        SlotMachine();
        ~SlotMachine();
        void MakeBet(int betAmount);
        void SpinMachine();
        int NewBalance();
        int getBet();

};

#endif
