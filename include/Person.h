#ifndef PLAYER_H
#define PLAYER_H


#include <string>

using namespace std;



class Player 
{

    private:
        int _balance;
        string _name;

        
    public:
        //constructor//
        Player (int inputBalance, string inputName);

        //destructor
        ~Player();

        //stat checkers//
        int checkBalance();



        void addBalance(int addAmount);
        void subtractBalance(int subtractAmount);



        string getName();
        

};

#endif
