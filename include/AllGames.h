#ifndef ALLGAMES_H
#define ALLGAMES_H

#include "Blackjack.h"
#include "Roulette.h"
#include "Person.h"
#include "Card.h"
#include "Deck.h"
#include "Poker.h"
#include "PokerPlayer.h"
#include "SlotMachine.h"


void blackjackMain(Player *mainPlayer)
{
  bool cont = true;
	char checkCont;
	int blackjackBet;
	int blackjackOption;

	do
	{
		cout << "How much would you like to bet?: ";
		cin >> blackjackBet;

		while(cin.fail() || blackjackBet > mainPlayer->checkBalance() || blackjackBet <= 0)
		{
			if(cin.fail())
			{
				cout << "ERROR: Please enter an integer: " << endl;
				cin.clear();
			}
			else if(blackjackBet > mainPlayer->checkBalance())
			{
				cout << "ERROR: Your bet is greater than your balance, please reconsider: " << endl;
			}
			else if(blackjackBet <= 0)
			{
				cout << "ERROR: Your bet is lower than 1, please enter a higher bet: " << endl;
			}
			cin.clear();
			cin.ignore(123, '\n');
			cin >> blackjackBet;
		}
		cin.clear();
		cin.ignore(123, '\n');
		
		Blackjack thePlayer;

		thePlayer.bet(blackjackBet);

		while(!thePlayer.gameStatus())
		{
            if(thePlayer.handSize() == 2)
            {
                cout << "What would you like to do:"
                     << "\n(1) Hit"
                     << "\n(2) Stand"
                     << "\n(3) Double Down"
                     << endl;
				cin >> blackjackOption;
				while(cin.fail() || blackjackOption >= 3 || blackjackOption < 1)
				{
					if(cin.fail())
					{
						cout << "ERROR: Please enter an integer: " << endl;
						cin.clear();
					}
					if(blackjackOption > 3 || blackjackOption < 1)
					{
						cout << "ERROR: Invalid option, please enter a valid one: " << endl;
					}
					if(blackjackOption == 3)
					{
						if(blackjackBet*2 > mainPlayer->checkBalance())
						{
							cout << "ERROR: You don't have enough to double down, pick another option: " << endl;
						}
						else {break;}
					}
					cin.clear();
					cin.ignore(123, '\n');
					cin >> blackjackOption;
				}
				cin.clear();
            }
            else
            {
                cout << "What would you like to do:"
                     << "\n(1) Hit"
                     << "\n(2) Stand"
                     << std::endl;
				cin >> blackjackOption;
				while(cin.fail() || blackjackOption > 2 || blackjackOption < 1)
				{
					if(cin.fail())
					{
						cout << "ERROR: Please enter an integer: " << endl;
						cin.clear();
					}
					if(blackjackOption > 2 || blackjackOption < 1)
					{
						cout << "ERROR: Invalid option, please enter a valid one: " << endl;
					}
					cin.clear();
					cin.ignore(123, '\n');
					cin >> blackjackOption;
				}
				cin.clear();
            }
			
			if(blackjackOption == 1) {thePlayer.hit();}
			else if(blackjackOption == 2) {thePlayer.stand();}
			else if(blackjackOption == 3) {blackjackBet = thePlayer.doubleDown();}
		}

		if(thePlayer.isWin())
		{
			mainPlayer->addBalance(blackjackBet);
			cout << "Your new balance is: " << mainPlayer->checkBalance() << endl;
		}
		else if(thePlayer.isDraw())
		{
			cout << "Your balance is still: " << mainPlayer->checkBalance() << endl;
		}
		else
		{
			mainPlayer->subtractBalance(blackjackBet);
			cout << "Your new balance is: " << mainPlayer->checkBalance() << endl;
		}

		cout << "Would you like to continue playing?(y/n): " << endl;
		cin >> checkCont;
		if(toupper(checkCont) != 'Y')
		{
			cont = false;
		}
		
	}while(cont);
}

void rouletteMain(Player *mainPlayer) {
  bool continueRoulette = true;
  char continueRouletteInput;
  do {

    cout << "Welcome to the Roulette Table " << mainPlayer->getName() << "!!" << endl; 

    cout << "so do you want bet on the color of the tile , or the value of the "
            "tile that the ball lands on?"
         << endl;

      
    cout << "Guessing the value is harder, but you will be rewarded much more "
            "than you would if you choose to guess the color ... choose wisely "
            ":)"
         << endl;
    
    cout
        << "please enter '0' if you want to bet on the color, and enter '1' if "
           "you want to bet on the value"
        << endl;
   
    int betType;
    cin >> betType;

    while (cin.fail()) {
      cout << "ERROR: Please enter '0' if you want to bet on the color, and enter '1' if you want to bet on the value" << endl;
      if (cin.fail()) {
        cin.clear();
      }
      cin.ignore(123, '\n');
      cin >> betType;
    }
    cin.clear();
    cin.ignore(123, '\n');

    
    cout
        << "now that you know what you are betting on, HOW MUCH do you want to "
           "put down? Please enter an integer:"
        << endl;

    int betAmount;
    cin >> betAmount;
    while (cin.fail() || betAmount > mainPlayer->checkBalance()) {
      if (cin.fail()) {
      cout << "ERROR:Please enter an integer.." << endl;
        cin.clear();
      }

      if (betAmount > mainPlayer->checkBalance()) {
        cout << "ERROR: The value you have chosen to bet is greater than your current balance, please reconsider:" << endl;
      }
      cin.clear();
      cin.ignore(123, '\n');
      cin >> betAmount;
    }
    cin.clear();
    cin.ignore(123, '\n');

    mainPlayer->subtractBalance(betAmount);

    Roulette *RouletteBoard = new Roulette();

    RouletteBoard->SpinBoard();

  

    if (betType == 0) {
      cout << "What color would you like to bet on, please enter a string , "
              "'red' 'black' or 'green'"
           << endl;
     string inputColor;
      cin >> inputColor;

      while ((inputColor != "green") && (inputColor != "black") &&
             (inputColor != "red")) {
        cout << "ERROR:Please enter a string , 'red' 'black' or 'green'"
             << endl;
        cin.clear();
        cin.ignore(123, '\n');
      }
      cin.clear();
      cin.ignore(123, '\n');
      RouletteBoard->BetColor(betAmount, inputColor);
      RouletteBoard->DisplayResults(0);
    }

    if (betType == 1) {
      cout << "What tile value would you like to bet on, please enter an integer "
              "from "
              "0 to 36:"
           << endl;
      int inputGuessValue;
      cin >> inputGuessValue;

      while (cin.fail() || (inputGuessValue < 0 && inputGuessValue > 36)) {
        cout << "ERROR: please enter an integer from 0 to 36:" << endl;
        cin.clear();
        cin.ignore(123, '\n');
      }
      cin.clear();
      cin.ignore(123, '\n');
      
      RouletteBoard->BetValue(betAmount, inputGuessValue);
      RouletteBoard->DisplayResults(1);
    }

    mainPlayer->addBalance(RouletteBoard->checkPlayerEarnings());
    delete RouletteBoard;
    cout << "updated balance is " << mainPlayer->checkBalance() << endl;
    
    cout << "Would you like to keep playing Roulette? (y/n):" << endl;
    cin >> continueRouletteInput;
    if ((toupper(continueRouletteInput)) != 'Y') {
      continueRoulette = false;
    }
    
  } while (continueRoulette);
  
}

void pokerMain(Player *mainPlayer)
{
  #include <iomanip>
  #include <iostream>
  #include <limits>

  char userChoice = 'Y';
  while (userChoice == 'Y')
  {
        PokerPlayer *mainPokerPlayer = new PokerPlayer((mainPlayer)->getName(), 
                                                        mainPlayer->checkBalance() - 100, 100);
    
        Poker *pokerGame = new Poker(&mainPokerPlayer, 100);
        pokerGame->NewHand();
        mainPlayer->addBalance(mainPokerPlayer->getGameBalance());

        std::cout << std::endl
                  << "Would you like to play again?  Y/N\n";

        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'Y' 
                                && toupper(userChoice) != 'N'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(123, '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }
  }
}

void slotMain(Player *mainPlayer)
{
    bool ExitOption = true;
    while(ExitOption){
        cout << "Welcome to the Slot Machine!" << endl;
        SlotMachine* PlayGame = new SlotMachine();
          
        int EarnedAmount;
        int Replay;
        int betAmount;
        int PlayerBalance;
        PlayerBalance = mainPlayer->checkBalance();
        cout << "Your current balance is: " <<   PlayerBalance << endl;
        cout << "How much are you willing to bet from your money?" << endl;
    
        cin >> betAmount;
        while (cin.fail() || betAmount > mainPlayer->checkBalance()) {
            if (cin.fail()) {
                cout << "ERROR:Please enter an integer.." << endl;
                cin.clear();
            }
            if (betAmount > mainPlayer->checkBalance()) {
                cout << "ERROR: The value you have chosen to bet is greater than your current balance, please reconsider:" << endl;
            }
            cin.clear();
            cin.ignore(123, '\n');
            cin >> betAmount;
        }
        cin.clear();
        cin.ignore(123, '\n');

        mainPlayer->subtractBalance(betAmount);
        PlayGame->MakeBet(betAmount);
        cout << "Lets start spinning!" << endl;
        
        PlayGame->SpinMachine();
        EarnedAmount = PlayGame->NewBalance();

        mainPlayer->addBalance(EarnedAmount);


        cout << "Your new balance is:  " << mainPlayer->checkBalance() << endl;
        cout << "Would you like to play again? (1) Yes (2) No" << endl;
        cin >> Replay;
        if(Replay ==2){
            ExitOption = false;
        }

    }
}


#endif
