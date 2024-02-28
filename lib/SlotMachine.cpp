#include <iostream>
#include <cstdlib>
#include "../include/SlotMachine.h"
#include "../include/Person.h"

using namespace std;

SlotMachine::SlotMachine(){
    
    item1 = 0;
    item2 = 0;
    item3 = 0;

    bet = 0;
    playercoins = 0;
    
}

SlotMachine::~SlotMachine(){

}

void SlotMachine::MakeBet(int betAmount){
    bet = betAmount;

}

void SlotMachine::SpinMachine(){
    item1 = rand()%9+1;
    item2 = rand()%9+1;
    item3 = rand()%9+1;

    cout <<  "|" << item1 << "|" << item2 << "|" << item3 << "|" << endl;

    if( playercoins > 0 ){
        if(item1 == item2 && item3 && playercoins >= bet){
            cout << "You won " << bet*5 << "coins!" << endl;
            playercoins = playercoins + bet*5;
            
        }
        else if(item1 != item2 && item3 && playercoins > bet-bet){
            cout << "You lost!" << endl;
        }
        
        else if(item1 == item2 or item3 && playercoins >= bet){
            cout << "You won " << bet *2 << "coins!" << endl;
            playercoins = playercoins + bet*2;
        }

        if( playercoins == 0 ){
            cout << " No more coins to play with!" << endl;
        }
        cout << "Thank you for playing!" << endl;
    }
}

int SlotMachine::NewBalance(){
    return playercoins;
}

int SlotMachine::getBet(){
    return bet;
}
