#include <cstdlib>
#include "../include/Deck.h"


//PUBLIC
Deck::Deck() 
{
    for (int i = 1; i <= 2; i++) 
    {
        _deckOfCards->push(Card(Card::Rank::ACE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::TWO, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::THREE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::FOUR, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::FIVE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::SIX, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::SEVEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::EIGHT, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::NINE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::TEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::JACK, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::QUEEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::KING, Card::Suit(i)));
    }

    for (int i = 3; i <= 4; i++) 
    {
        _deckOfCards->push(Card(Card::Rank::KING, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::QUEEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::JACK, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::TEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::NINE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::EIGHT, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::SEVEN, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::SIX, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::FIVE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::FOUR, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::THREE, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::TWO, Card::Suit(i)));
        _deckOfCards->push(Card(Card::Rank::ACE, Card::Suit(i)));
    }

     _rmngCards = _deckOfCards->size();
}

Deck::~Deck()
{
    delete _deckOfCards;
}

int Deck::getSize() const
{
    return _rmngCards;
}

bool Deck::IsEmpty() const
{
    return _rmngCards == 0;
}

void Deck::AddCard(Card card)
{
    _deckOfCards->push(card);
    _rmngCards++;
}

Card Deck::DrawCard()
{
    Card drawnCard = _deckOfCards->top();
    _deckOfCards->pop();
    _rmngCards--;

    return drawnCard;
}

void Deck::RiffleShuffle()
{
    //Splits the deck in half and allocates the top half
    //into the left-hand card pile.
    std::stack<Card> *lhsCards = new std::stack<Card>;
    while (getSize() > 26)
    {
        lhsCards->push(DrawCard());
    }

    //The remaining lower half of the deck becomes the
    //right-hand card pile.
    std::stack<Card> *rhsCards = new std::stack<Card>;
    while (!IsEmpty())
    {
        rhsCards->push(DrawCard());
    }

    //Riffles the two card piles together.
    //Stops when either card pile is empty.
    int randPile;
    std::stack<Card> *cardPiles[2] = {lhsCards, rhsCards};
    while (!lhsCards->empty() && 
           !rhsCards->empty())
    {
        randPile = rand() % 2;

        _deckOfCards->push(cardPiles[randPile]->top());
        cardPiles[randPile]->pop();
        _rmngCards++;
    }

    //Transfers remaining card pile onto the main deck.
    int rmngPile = (randPile - 1) * -1;
    while (!cardPiles[rmngPile]->empty())
    {
        _deckOfCards->push(cardPiles[rmngPile]->top());
        cardPiles[rmngPile]->pop();
        _rmngCards++;
    }

    //Deallocates card piles from memory.
    delete lhsCards;
    delete rhsCards;
}


//PRIVATE
bool Deck::operator==(Deck& rhs)
{
    //Compares size.
    bool isMatching = (getSize() == rhs.getSize());
    if (isMatching == false)
    {
        return isMatching;
    }

    //Compares order of cards.
    std::stack<Card> *lhsCards = new std::stack<Card>;
    std::stack<Card> *rhsCards = new std::stack<Card>;
    while (isMatching && !IsEmpty())
    {
        lhsCards->push(DrawCard());
        rhsCards->push(rhs.DrawCard());
        if (!(lhsCards->top() == rhsCards->top()))
        {
            isMatching = false;
        }
    }

    //Returns decks to original order.
    while (!lhsCards->empty())
    {
        AddCard(lhsCards->top());
        lhsCards->pop();
        rhs.AddCard(rhsCards->top());
        rhsCards->pop();
    }

    //Deallocates card piles from memory.
    delete lhsCards;
    delete rhsCards;
    
    return isMatching;
}

