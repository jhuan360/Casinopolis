#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stack>
#include "Deck.h"
#include "Person.h"

class Blackjack
{
    private:
		// Player blackjackPlayer()
		// int currentBet;
        Deck _theDeck;
		//11 is max number of cards possible before bust
        Card *_yourHand = new Card[11];
		int yourHandSize = 0;
		int yourLowerHandTotal = 0;
		int yourUpperHandTotal = 0;
		Card *_dealerHand = new Card[11];
		int dealerHandSize = 0;
		int dealerLowerHandTotal = 0;
		int dealerUpperHandTotal = 0;
		bool bust = false;
		bool win = false;
		bool draw = false;
		bool yourTurn = true;
		bool dealerTurn = false;
		bool gameOver = false;
		int currentBet = 0;

    public:
        // instantiating the game.
        Blackjack();

        //BlackjackPlayer destructor.
        ~Blackjack();

        // shows the player's current hand.
        void showYourHand();

		// shows the dealers current hand.
		void showDealerHand();

		// calculate's the total value in your hand.
		void calculateYourTotal();

		// calculate's the total value in dealer hand.
		void calculateDealerTotal();

		// prints out your hand's total.
		void displayYourTotal();

		// prints out dealer's hand's total.
		void displayDealerTotal();

		// compares the total from player and dealer to determine a winner.
		void compareTotal();

        // gives the player a new card.
        void hit();

        // the player keeps their current hand.
        void stand();

        /* allows the player to increase their initial bet by 100%,
           but they must stand after drawing their next card.*/ 
        int doubleDown();

        // how much the player wants to bet.
        void bet(int);

        // returns the value of the card as an int.
        int rankToInt(Card::Rank rank, bool turn);

        // returns your current hand size.
        int handSize();

		// returns if the game is a bust or not.
		bool gameStatus();

		// returns true if player wins.
		bool isWin();

		// returns true if game is a draw.
		bool isDraw();
};

#endif
