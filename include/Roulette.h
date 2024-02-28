#ifndef ROULETTE_H
#define ROULETTE_H
#include <string>
#include <cstdlib>
#include <iostream>
#include "../include/Person.h"

using namespace std;

class Roulette {

private:
//randomly generated values
    int _boardValue;
    string _boardColor;
//player chosen values that will be set and compared 
    int _playerValue;
    string _playerColor;

    int _playerEarnings;


public:
//constructor 
    Roulette();
//destructor
    ~Roulette();

    void SpinBoard();
    void BetColor(int betAmount, string colorChoice);
    void BetValue(int betAmount, int valueChoice);
    void DisplayResults(int betType);

    int checkPlayerEarnings();

};


#endif