#include "../include/Roulette.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;



Roulette::Roulette() {
    _boardValue = 0;
    _boardColor = "";
    _playerValue = 0;
    _playerColor = "";
    _playerEarnings = 0;
}


Roulette::~Roulette() {

}

void Roulette::SpinBoard() {
//randomizing valUE that ball lands on
_boardValue =  rand() % 37;
//setting color of the the spot that it landed on 
//based on the value according to roulette rules and ranges
if (_boardValue == 0 ){
    _boardColor = "green";
}

else if ((_boardValue >= 1) && (_boardValue <= 10)){
    if (_boardValue % 2 == 0) {
        _boardColor = "black";
    }
    else {
        _boardColor = "red";
    }
}

else if ((_boardValue >= 19) && (_boardValue <= 28)){
    if (_boardValue % 2 == 0) {
        _boardColor = "black";
    }
    else {
        _boardColor = "red";
    }
}

else if ((_boardValue >= 11) && (_boardValue <= 18)){
    if (_boardValue % 2 == 0) {
        _boardColor = "red";
    }
    else {
        _boardColor = "black";
    }
}

else if ((_boardValue >= 29) && (_boardValue <= 36)){
    if (_boardValue % 2 == 0) {
        _boardColor = "red";
    }
    else {
        _boardColor = "black";
    }
}

}


void Roulette::BetColor(int betAmount, string colorChoice) {
_playerColor = colorChoice;
if (_playerColor == _boardColor) {
    _playerEarnings = betAmount * 2;
}
}

void Roulette::BetValue(int betAmount,int valueChoice) {
    _playerValue = valueChoice;
if (_playerValue == _boardValue) {
    _playerEarnings = betAmount * 5;
}

}
void Roulette::DisplayResults(int betType) {

cout << "Drumroll please..........." << endl;
cout << "The ball has landed on tile #" << _boardValue  << endl;
cout << " which is a " <<  _boardColor << " colored tile" << endl;

if (betType == 0) {
    cout << "You chose to bet on the color of the tile and..." << endl;
    if (_playerColor == _boardColor) {
        cout << "Congratulations you guessed correctly and doubled your money!!" << endl;
    }
    else {
        cout << "Unfortunately, you guessed wrong and win nothing :(" << endl;
    }
}


if (betType == 1) {
    cout << "You chose to bet on the value of the tile and..." << endl;
    if (_playerValue == _boardValue) {
        cout << "Congratulations you guessed correctly and QUINTUPLED your money!!" << endl;
    }
    else {
        cout << "Unfortunately, you guessed wrong and win nothing :(" << endl;
    }
}

cout << "Your total earnings after this round is " << _playerEarnings << endl;

}


int Roulette::checkPlayerEarnings() {
    return _playerEarnings;
}