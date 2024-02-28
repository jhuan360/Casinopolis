#ifndef CARD_H
#define CARD_H


#include <string>


class Card 
{
public:
    enum class Rank 
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13
    };
    enum class Suit 
    {
        SPADES = 1,
        DIAMONDS = 2,
        CLUBS = 3,
        HEARTS = 4
    };

private:
    Rank _rank;
    Suit _suit;
    
public:
	//Empty constructor
	Card(){}

    //Constructs a new card from the rank and the suit passed in.
    Card(Rank rank, Suit suit);

    //Returns the rank of the card.
    Rank getRank() const;
    
    //Returns the suit of the card.
    Suit getSuit() const;

    //Returns the rank as a string for blackjack
    std::string rankToString(Rank);

    //Returns the suit as a string for blackjack
    std::string suitToString(Suit);

    //Returns the rank and the suit of the card as a string for poker.
    std::string PrintCard() const;

    // prints card rank and suit for blackjack.
    void printCard();

    //Overrides equal-to operator.
    //Returns 'true' if two cards are matching.
    bool operator==(const Card& rhs) const;

    void operator=(const Card& rhs);

private:
    //Returns the rank of the card as a string.
    std::string RankToString() const;

    //Returns the suit of the card as a string.
    std::string SuitToString() const;
    
};


#endif

