#ifndef POKERPLAYER_H
#define POKERPLAYER_H


#include <string>
#include "../include/Card.h"
#include "../include/Person.h"


class PokerPlayer : public Player
{
private:
    //The player's game balance is initially equal to the buy-in.
    double _gameBalance;
    //players name
    std::string _playerName;
    //Stores up to two hole cards and five community cards.
    Card **_cards = new Card*[7] {nullptr};

    //The number of cards available to the player.
    int _numCards = 0;

    //The community cards dealt to the board throughout a game of poker.
    Card **_communityCards = new Card*[5] {nullptr};

    //The number of cards on the board.
    int _numCommunityCards = 0;

    //The hole cards dealt to the player during the preflop round.
    Card **_holeCards = new Card*[2] {nullptr};

    //The number of hole cards in the player's possession.
    int _numHoleCards = 0;

    //Whether the player has checked in the current betting round.
    bool _firstToAct = 0;

    //Whether the player has checked in the current betting round.
    bool _checked = 0;

    //Whether the player has folded in the current betting round.
    bool _folded = 0;

    //Whether the player has gone all-in in the current poker game.
    bool _allIn = 0;

    //The player's current bet
    double _currBet = 0;

public:
    //Constructs a poker player with a game balance equal to the buy-in of the game.
    PokerPlayer(std::string name, int balance, double gameBalance);

    //Deallocates the player's hole cards.
    ~PokerPlayer();

    //Returns the player's remaining game balance.
    double getGameBalance() const;

    //Returns 'true' if the player is first to act.
    bool IsFirstToAct() const;

    //Marks player as first to act.
    void SetFirstAct();

    //Returns 'true' if the player has checked.
    bool HasChecked() const;

    //Unchecks the player.
    void Uncheck();

    //Returns 'true' if the player has folded.
    bool HasFolded() const;

    //Returns 'true' if the player has gone all-in.
    bool IsAllIn() const;

    //Check the player's current bet
    double CheckBet() const;

    //Returns the player's hand ranking in numerical form.
    int getHandRank() const;

    //Returns the player's hand height in numerical form.
    int getHandHeight();

    //Returns the player's hand as a string.
    std::string ShowHand();

    //Prints the player's hole cards.
    void PrintHoleCards() const;

    //Links the player to the poker session's community cards.
    void setCommunityCard(Card communityCard);

    //Sets the player's hole cards.
    void setHoleCard(Card holeCard);

    //The player is first to act.
    void setFirstAct();

    //Places a small blind on behalf of the player.
    double BlindBet(double cost);

    //The player checks.
    double Check();

    //The player folds.
    double Fold();

    //The player calls the current bet.
    double Call(double currBet);

    //The player places an initial bet.
    double Bet();
    
    //The player places an initial bet.
    double Raise(double currBet);

    //The player goes all-in.
    double AllIn(double currBet);

    //Refunds the player.
    void Return(double refund);

    //Rewards the player.
    void Wins(double amount);

private:
    //Returns the player's hand ranking as a string.
    std::string ShowHandRank() const;

    //Returns the player's hand height as a string.
    std::string ShowHandHeight();

    //Sorts the cards by rank.
    void SortCardsByRank();

    //Sorts the cards by suit.
    void SortCardsBySuit();
};


#endif

