#ifndef DECK_H
#define DECK_H


#include <stack>
#include "Card.h"


class Deck
{
private:
    std::stack<Card> *_deckOfCards = new std::stack<Card>;

    //Number of cards remaining in the deck.
    int _rmngCards;
    
public:
    //Constructs a newly unboxed, face-down standard deck of cards.
    //A standard deck of cards contains every rank in four different suits.
    Deck();

    //Removes cards one by one from the top of the deck and deallocates memory.
    ~Deck();

    //Returns the number of cards remaining in the deck.
    int getSize() const;

    //Returns 'true' if there are no remaining cards in the deck.
    bool IsEmpty() const;

    //Adds a card to the top of the face-down deck.
    void AddCard(Card card);

    //Draws a card from the top of the face-down deck.
    Card DrawCard();

    //Performs a standard riffle shuffle on the deck.
    void RiffleShuffle();

private:
    //Overrides equal-to operator.
    //Returns 'true' if two decks have matching contents.
    friend class DeckTests_ShufflesDeck_Test;
    bool operator==(Deck& rhs);
};


#endif

