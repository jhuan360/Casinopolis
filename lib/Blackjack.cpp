#include "../include/Blackjack.h"
#include <iostream>

Blackjack::Blackjack()
{
	for(int i = 0; i < 7; i++)	// shuffles the deck 7 times (standard).
	{
		_theDeck.RiffleShuffle();
	}
	std::cout << "The deck has been shuffled..." << std::endl;
	
	for(int i = 0; i < 2; i++)	// gives the player and dealer 2 cards each.
	{
		_yourHand[i] = _theDeck.DrawCard();
		yourHandSize++;
		_dealerHand[i] = _theDeck.DrawCard();
		dealerHandSize++;
	}
	//displays current hand and total.
	Blackjack::showYourHand();
	Blackjack::calculateYourTotal();
	Blackjack::displayYourTotal();
}

Blackjack::~Blackjack()
{
	delete[] _yourHand;
	delete[] _dealerHand;
}

void Blackjack::showYourHand()
{
	std::cout << "Your current hand:" << std::endl;
	for(int i = 0; i < yourHandSize; i++)
	{
		_yourHand[i].PrintCard();
	}
}

void Blackjack::showDealerHand()
{
	std::cout << "Dealer's current hand: " << std::endl;
	for(int i = 0; i < dealerHandSize; i++)
	{
		_dealerHand[i].PrintCard();		
	}
}

void Blackjack::calculateYourTotal()
{
	// two different totals in case of an Ace, which can equal 1 or 11.
	this->yourLowerHandTotal = 0;
	this->yourUpperHandTotal = 0;
	for(int i = 0; i < yourHandSize; i++)
	{
		Card::Rank rank = _yourHand[i].getRank();
		// if card is an Ace, then totals are added in switch instead.
		if(rank == Card::Rank::ACE)
		{
			this->yourLowerHandTotal += rankToInt(rank, yourTurn);
		}
		else
		{
			this->yourLowerHandTotal += rankToInt(rank, yourTurn);
			this->yourUpperHandTotal += rankToInt(rank, yourTurn);
		}
	}
}

// exact same calculations, but for dealer's hand.
void Blackjack::calculateDealerTotal()
{
	this->dealerLowerHandTotal = 0;
	this->dealerUpperHandTotal = 0;
	for(int i = 0; i < dealerHandSize; i++)
	{
		Card::Rank rank = _dealerHand[i].getRank();
		if(rank == Card::Rank::ACE)
		{
			this->dealerLowerHandTotal += rankToInt(rank, yourTurn);
		}
		else
		{
			this->dealerLowerHandTotal += rankToInt(rank, yourTurn);
			this->dealerUpperHandTotal += rankToInt(rank, yourTurn);
		}
	}
}

// displays your total properly depending on totals from lower and upper.
void Blackjack::displayYourTotal()
{
	std::cout << "Your current total: ";
	if(this->yourLowerHandTotal > 21)
	{
		bust = true;
		gameOver = true;
		std::cout << yourLowerHandTotal << ", you busted!" << std::endl;
	}
	// if the values are equal then only one is necessary.
	else if(this->yourLowerHandTotal == this->yourUpperHandTotal)
	{
		std::cout << yourUpperHandTotal << std::endl;
	}
	// if upper total is greater than 21, then it only shows your lower total.
	else if(this->yourUpperHandTotal > 21)
	{
		std::cout << yourLowerHandTotal << std::endl;
	}
	else if(this->yourUpperHandTotal == 21)
	{
		std::cout << yourUpperHandTotal << std::endl;
	}
	// if lower total != upper total, display both totals for the player.
	else
	{
		std::cout << yourLowerHandTotal << " or " << yourUpperHandTotal << std::endl;
	}
}

// exact same as displayPlayerTotal(), but for the dealer.
void Blackjack::displayDealerTotal()
{
	std::cout << "Dealer's current total: ";
	if(this->dealerLowerHandTotal > 21)
	{
		std::cout << dealerLowerHandTotal << std::endl;
	}
	else if(this->dealerLowerHandTotal == this->dealerUpperHandTotal)
	{
		std::cout << dealerUpperHandTotal << std::endl;
	}
	else if(this->dealerUpperHandTotal > 21)
	{
		std::cout << dealerLowerHandTotal << std::endl;
	}
	else if(this->dealerUpperHandTotal == 21)
	{
		std::cout << dealerUpperHandTotal << std::endl;
	}
	else
	{
		std::cout << dealerLowerHandTotal << " or " 
				  << dealerUpperHandTotal << std::endl;
	}
}

// compares all possible outcomes to determine if the winner or if there is a draw.
void Blackjack::compareTotal()
{
	// checks if you busted before checking other code.
	if(bust)
	{
		win = false;
		draw = false;
	}
	// compares both upper totals
	else if(dealerUpperHandTotal <= 21 && yourUpperHandTotal <= 21)
	{
		// checks if both the player and the dealer have naturals
		if(dealerUpperHandTotal == 21 && yourUpperHandTotal == dealerUpperHandTotal)
		{
			if(dealerHandSize == 2 && yourHandSize == dealerHandSize) {draw = true;}
			else if(yourHandSize == 2 && yourHandSize != dealerHandSize) {win = true;}
		}
		else if(dealerUpperHandTotal == yourUpperHandTotal) {draw = true;}
		else if(yourUpperHandTotal > dealerUpperHandTotal) {win = true;}
	}
	else if(dealerUpperHandTotal < 21 && yourUpperHandTotal > 21)
	{
		if(dealerUpperHandTotal == yourLowerHandTotal) {draw = true;}
		else if(yourLowerHandTotal > dealerUpperHandTotal) {win = true;}
	}
	else if(dealerUpperHandTotal > 21 && yourUpperHandTotal < 21)
	{
		if(dealerLowerHandTotal == yourUpperHandTotal) {draw = true;}
		else if(yourUpperHandTotal > dealerLowerHandTotal) {win = true;}
	}
	else
	{
		if(dealerLowerHandTotal == yourLowerHandTotal){draw = true;}
		else if(yourLowerHandTotal > dealerLowerHandTotal) {win = true;}
	}
}

void Blackjack::hit()
{
	// adds another card to the player's hand.
    _yourHand[yourHandSize] = _theDeck.DrawCard();
	yourHandSize++;
	std::cout << "Card has been added to your hand..." << std::endl;
	// displays current hand and total for the player.
	Blackjack::showYourHand();
	Blackjack::calculateYourTotal();
	Blackjack::displayYourTotal();
}

void Blackjack::stand()	// signifies the end of the player's turn.
{
	yourTurn = false;
	dealerTurn = true;

	std::cout << "It is now the dealer's turn..." << std::endl;

	Blackjack::showDealerHand();
	Blackjack::calculateDealerTotal();
	Blackjack::displayDealerTotal();
	
	while(dealerTurn)
	{
		if(dealerLowerHandTotal > 21 && !bust)
		{
			win = true;
			dealerTurn = false;
			gameOver = true;
			std::cout << "The dealer busted... you WIN!" << std::endl;
		}
		else if(dealerUpperHandTotal == 21)
		{
			dealerTurn = false;
			gameOver = true;
			Blackjack::compareTotal();
			if(draw) {std::cout << "It was a draw... you get your money back." << std::endl;}
			else if(win) {std::cout << "You were closer to 21, you WIN!" << std::endl;}
			else if(bust) {std::cout << "You busted, you LOSE!" << std::endl;}
			else {std::cout << "The dealer was closer to 21, you LOSE!" << std::endl;}
		}
		else if(dealerUpperHandTotal >= 17 || dealerLowerHandTotal >= 17)
		{
			dealerTurn = false;
			gameOver = true;
			Blackjack::compareTotal();
			if(draw) {std::cout << "It was a draw... you get your money back." << std::endl;}
			else if(win) {std::cout << "You were closer to 21, you WIN!" << std::endl;}
			else if(bust) {std::cout << "You busted, you LOSE!";}
			else {std::cout << "The dealer was closer to 21, you LOSE!" << std::endl;}
		}
		else
		{
			_dealerHand[dealerHandSize] = _theDeck.DrawCard();
			dealerHandSize++;
			std::cout << "The dealer drew a card..." << std::endl;
			Blackjack::showDealerHand();
			Blackjack::calculateDealerTotal();
			Blackjack::displayDealerTotal();
		}
		
	}
}

int Blackjack::doubleDown()
{
	this->currentBet *= 2;
	std::cout << "The current bet is now: " << this->currentBet << "\n" << std::endl;
	_yourHand[yourHandSize] = _theDeck.DrawCard();
	yourHandSize++;
	Blackjack::showYourHand();
	Blackjack::calculateYourTotal();
	Blackjack::displayYourTotal();
	Blackjack::stand();

	return currentBet;
}

void Blackjack::bet(int bet)
{
	this->currentBet += bet;
	std::cout << "The current bet is: " << this->currentBet << "\n" << std::endl;
}

// switch statement to convert card ranks into integer values to be added to the totals.
int Blackjack::rankToInt(Card::Rank rank, bool turn)
{
	switch(rank)
	{
		case Card::Rank::ACE:
			if(turn)
			{	
				this->yourLowerHandTotal += 1;
				this->yourUpperHandTotal += 11;
			}
			else
			{
				this->dealerLowerHandTotal += 1;
				this->dealerUpperHandTotal += 11;
			}
			return 0;
			break;
		case Card::Rank::TWO:
			return 2;
			break;
		case Card::Rank::THREE:
			return 3;
			break;
		case Card::Rank::FOUR:
			return 4;
			break;
		case Card::Rank::FIVE:
			return 5;
			break;
		case Card::Rank::SIX:
			return 6;
			break;
		case Card::Rank::SEVEN:
			return 7;
			break;
		case Card::Rank::EIGHT:
			return 8;
			break;
		case Card::Rank::NINE:
			return 9;
			break;
		case Card::Rank::TEN:
			return 10;
			break;
		case Card::Rank::JACK:
			return 10;
			break;
		case Card::Rank::QUEEN:
			return 10;
			break;
		case Card::Rank::KING:
			return 10;
			break;
		default:
			return 0;
			break;	
	}
}

int Blackjack::handSize()
{
	return yourHandSize;
}

// used to check the status of the game.
bool Blackjack::gameStatus() {return gameOver;}

bool Blackjack::isWin() {return win;}

bool Blackjack::isDraw() {return draw;}
