#include "../include/Card.h"
#include <iostream>


//PUBLIC
Card::Card(Rank rank, Suit suit)
{
	_rank = rank;
	_suit = suit;
}

Card::Rank Card::getRank() const 
{
    return _rank;
}

Card::Suit Card::getSuit() const
{
    return _suit;
}

std::string Card::PrintCard() const
{
	return RankToString() + " of " + SuitToString();
}

std::string Card::rankToString(Rank)
{
    switch(_rank)
    {
        case Card::Rank::ACE:
            return "Ace";
            break;
		case Card::Rank::TWO:
			return "Two";
			break;
		case Card::Rank::THREE:
            return "Three";
            break;
		case Card::Rank::FOUR:
			return "Four";
			break;
		case Card::Rank::FIVE:
            return "Five";
            break;
		case Card::Rank::SIX:
			return "Six";
			break;
		case Card::Rank::SEVEN:
            return "Seven";
            break;
		case Card::Rank::EIGHT:
			return "Eight";
			break;
		case Card::Rank::NINE:
            return "Nine";
            break;
		case Card::Rank::TEN:
			return "Ten";
			break;
		case Card::Rank::JACK:
            return "Jack";
            break;
		case Card::Rank::QUEEN:
			return "Queen";
			break;
		case Card::Rank::KING:
			return "King";
			break;
        default:
            return "Not a valid Card";
            break;
    }
}

std::string Card::suitToString(Suit)
{
	switch(_suit)
	{
		case Card::Suit::SPADES:
			return "spades";
			break;
		case Card::Suit::HEARTS:
			return "hearts";
			break;
		case Card::Suit::CLUBS:
			return "clubs";
			break;
		case Card::Suit::DIAMONDS:
			return "diamonds";
			break;
        default:
            return "Not a valid Card";
            break;
	}
}

void Card::printCard()
{
    std::string rank = rankToString(this->getRank());
	std::string suit = suitToString(this->getSuit());
	std::cout << rank << " of " << suit << std::endl;
}

bool Card::operator==(const Card& rhs) const
{
    return (this->getRank() == rhs.getRank() 
         && this->getSuit() == rhs.getSuit());
}

void Card::operator=(const Card& rhs)
{
    _rank = rhs.getRank();
    _suit = rhs.getSuit();
}


//PRIVATE
std::string Card::RankToString() const
{
    switch(_rank)
    {
        case Rank::ACE:
            return "Ace";
            break;
		case Rank::TWO:
			return "Two";
			break;
		case Rank::THREE:
            return "Three";
            break;
		case Rank::FOUR:
			return "Four";
			break;
		case Rank::FIVE:
            return "Five";
            break;
		case Rank::SIX:
			return "Six";
			break;
		case Rank::SEVEN:
            return "Seven";
            break;
		case Rank::EIGHT:
			return "Eight";
			break;
		case Card::Rank::NINE:
            return "Nine";
            break;
		case Rank::TEN:
			return "Ten";
			break;
		case Rank::JACK:
            return "Jack";
            break;
		case Rank::QUEEN:
			return "Queen";
			break;
		case Rank::KING:
			return "King";
			break;
    }
}

std::string Card::SuitToString() const
{
	switch(_suit)
	{
		case Suit::SPADES:
			return "Spades";
			break;
		case Suit::DIAMONDS:
			return "Diamonds";
			break;
		case Suit::CLUBS:
			return "Clubs";
			break;
		case Suit::HEARTS:
			return "Hearts";
			break;		
	}
}

