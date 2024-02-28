#ifndef POKER_H
#define POKER_H


#include "../include/Deck.h"
#include "../include/PokerPlayer.h"


class Poker
{
private:
    //This is the deck from which the community cards will be dealt.
    //The deck should be shuffled at the start of every hand.
    Deck _deckOfCards;

    //A total of five community cards, from which players can form a hand, will be dealt face-up 
    //to the center of the table as the game progresses.
    Card **_communityCards = new Card*[5] {nullptr};

    //The number of community cards that have been placed.
    int _numCommunityCards = 0;

    //This will be a heads-up poker session between two players, no-limit Texas Hold 'Em style.
    PokerPlayer *_dealer = nullptr;
    PokerPlayer *_opponent = nullptr;

    //The sum of money that players wager during a single game.
    double _mainPot = 0;

    //The buy-in is representative of 100 big blinds and 200 small blinds.
    double _buyInAmount;

public:
    //Starts a new poker session and picks a cards dealer at random.
    Poker(PokerPlayer **mainPlayer, double buyInAmount);

    //Deallocates the community cards.
    ~Poker();

    //The dealer places the small blind and their opponent places the big blind, as is the case
    //in a heads-up poker session.
    //Afterwards, the dealer shuffles the deck.
    void NewHand();

    //All players are dealt two hole cards.
    //The dealer is the first to act.
    void PreFlop();

    //Three community cards are dealt.
    //The dealer acts last and continues to do so for the remainder of the hand.
    void Flop();

    //A fourth community card is dealt.
    void Turn();

    //The fifth community card is dealt.
    void River();

    //Should multiple players remain after the last betting round, they must flip their cards.
    //The player with the highest hand takes the pot.
    void Showdown();

    //Ends the game.
    void EndGame();

private:
    void PrintCommunityCards() const;

    double NextMove(PokerPlayer **actingPlayer, double highestBet, double netAmount);
    
    char getPlayerAction(PokerPlayer ***actingPlayer, double highestBet);
};


#endif

