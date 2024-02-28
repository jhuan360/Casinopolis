

#include "../include/Person.h"
#include <string>

using namespace std;


Player::Player (int inputBalance, string inputName) {

    _balance = inputBalance;
    _name = inputName;
}



Player::~Player() {
    
}


string Player::getName() {
    return _name;
}

int Player::checkBalance() {
    return _balance;
}


void Player::addBalance(int addAmount) {
    _balance = _balance + addAmount;
}
void Player::subtractBalance(int subtractAmount) {
    _balance = _balance - subtractAmount;

}

