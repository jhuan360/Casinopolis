#include <iomanip>
#include <iostream>
#include <limits>
#include "../include/Poker.h"


//PUBLIC
Poker::Poker(PokerPlayer **mainPlayer, double buyInAmount)
{
    //Set the buy-in amount.
    _buyInAmount = buyInAmount;

    //Pick a cards dealer at random.
    if (rand() % 2)
    {
        _dealer = *mainPlayer;
        _opponent = new PokerPlayer("Sherlock Holmes", 1000, buyInAmount);
    }
    else
    {
        _dealer = new PokerPlayer("Sherlock Holmes", 1000, buyInAmount);
        _opponent = *mainPlayer;
    }
}

Poker::~Poker()
{
    //Deallocate memory for individual community cards.
    delete _communityCards[0];
    delete _communityCards[1];
    delete _communityCards[2];
    delete _communityCards[3];
    delete _communityCards[4];

    //Deallocate memory for the array of community cards.
    delete[] _communityCards;
}

void Poker::NewHand()
{
    std::cout << _dealer->getName() << " bought-in with $" << std::fixed << std::setprecision(2) << _dealer->getGameBalance() << "\n";
    std::cout << _opponent->getName() << " bought-in with $" << std::fixed << std::setprecision(2) << _opponent->getGameBalance() << "\n";
    std::cout << std::endl;


    //Shuffle the deck multiple times.
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();
    _deckOfCards.RiffleShuffle();

    //Blind bets are placed.
    _mainPot += _dealer->BlindBet(_buyInAmount / 200);
    std::cout << _dealer->getName() << " placed a small blind of $" << std::fixed << std::setprecision(2) << _buyInAmount / 200 << "\n";
    _mainPot += _opponent->BlindBet(_buyInAmount / 100);
    std::cout << _opponent->getName() << " placed a big blind of $" << std::fixed << std::setprecision(2) << _buyInAmount / 100 << "\n";
    std::cout << std::endl;

    PreFlop();
}

void Poker::PreFlop()
{
    //Deal hole cards according to heads-up rules.
    for (int i = 0; i < 2; i++)
    {
        _dealer->setHoleCard(_deckOfCards.DrawCard());
        _opponent->setHoleCard(_deckOfCards.DrawCard());
    }

    //The dealer acts last.
    _opponent->setFirstAct();
    _mainPot += NextMove(&_opponent, _opponent->CheckBet(), 0);
    std::cout << std::endl;
    std::cout << "Main pot: $" << std::fixed << std::setprecision(2) << _mainPot << "\n";
    std::cout << std::endl;
    if (_dealer->HasFolded())
    {
        _opponent->Wins(_mainPot);
        EndGame();
    }
    else if (_opponent->HasFolded())
    {
        _dealer->Wins(_mainPot);
        EndGame();
    }
    else if (_dealer->IsAllIn() || _opponent->IsAllIn())
    {
        Showdown();
    }
    else
    {
        _dealer->Uncheck();
        _opponent->Uncheck();

        std::cout << std::endl;

        Flop();
    }
}

void Poker::Flop()
{
    //Place three community cards.
    Card card1 = _deckOfCards.DrawCard();
    _communityCards[0] = new Card(card1.getRank(), card1.getSuit());
    _dealer->setCommunityCard(card1);
    _opponent->setCommunityCard(card1);
    std::cout << _dealer->getName() << " places " << _communityCards[0]->PrintCard() << " on the board\n";
    _numCommunityCards++;

    Card card2 = _deckOfCards.DrawCard();
    _communityCards[1] = new Card(card2.getRank(), card2.getSuit());
    _dealer->setCommunityCard(card2);
    _opponent->setCommunityCard(card2);
    std::cout << _dealer->getName() << " places " << _communityCards[1]->PrintCard() << " on the board\n";
    _numCommunityCards++;

    Card card3 = _deckOfCards.DrawCard();
    _communityCards[2] = new Card(card3.getRank(), card3.getSuit());
    _dealer->setCommunityCard(card3);
    _opponent->setCommunityCard(card3);
    std::cout << _dealer->getName() << " places " << _communityCards[2]->PrintCard() << " on the board\n";
    _numCommunityCards++;

    //Give players access to the community cards.
    for (int i = 0; i < 3; i++)
    {
        _dealer->setCommunityCard(*_communityCards[i]);
        _opponent->setCommunityCard(*_communityCards[i]);
    }

    //The dealer acts last.
    _opponent->setFirstAct();
    _mainPot += NextMove(&_opponent, _opponent->CheckBet(), 0);
    std::cout << std::endl;
    std::cout << "Main pot: $" << std::fixed << std::setprecision(2) << _mainPot << "\n";
    std::cout << std::endl;
    if (_dealer->HasFolded())
    {
        _opponent->Wins(_mainPot);
        EndGame();
    }
    else if (_opponent->HasFolded())
    {
        _dealer->Wins(_mainPot);
        EndGame();
    }
    else if (_dealer->IsAllIn() || _opponent->IsAllIn())
    {
        Showdown();
    }
    else
    {
        _dealer->Uncheck();
        _opponent->Uncheck();

        std::cout << std::endl;

        Turn();
    }
}

void Poker::Turn()
{
    //Place a community card.
    Card card4 = _deckOfCards.DrawCard();
    _communityCards[3] = new Card(card4.getRank(), card4.getSuit());
    _dealer->setCommunityCard(card4);
    _opponent->setCommunityCard(card4);
    std::cout << _dealer->getName() << " places " << _communityCards[3]->PrintCard() << " on the board\n";
    _numCommunityCards++;

    //Give players access to the community cards.
    for (int i = 3; i < 4; i++)
    {
        _dealer->setCommunityCard(*_communityCards[i]);
        _opponent->setCommunityCard(*_communityCards[i]);
    }

    //The dealer acts last.
    _opponent->setFirstAct();
    _mainPot += NextMove(&_opponent, _opponent->CheckBet(), 0);
    std::cout << std::endl;
    std::cout << "Main pot: $" << std::fixed << std::setprecision(2) << _mainPot << "\n";
    std::cout << std::endl;
    if (_dealer->HasFolded())
    {
        _opponent->Wins(_mainPot);
        EndGame();
    }
    else if (_opponent->HasFolded())
    {
        _dealer->Wins(_mainPot);
        EndGame();
    }
    else if (_dealer->IsAllIn() || _opponent->IsAllIn())
    {
        Showdown();
    }
    else
    {
        _dealer->Uncheck();
        _opponent->Uncheck();

        std::cout << std::endl;

        River();
    }
}

void Poker::River()
{
    //Place a community card.
    Card card5 = _deckOfCards.DrawCard();
    _communityCards[4] = new Card(card5.getRank(), card5.getSuit());
    _dealer->setCommunityCard(card5);
    _opponent->setCommunityCard(card5);
    std::cout << _dealer->getName() << " places " << _communityCards[4]->PrintCard() << " on the board\n";
    _numCommunityCards++;

    //Give players access to the community cards.
    for (int i = 4; i < 5; i++)
    {
        _dealer->setCommunityCard(*_communityCards[i]);
        _opponent->setCommunityCard(*_communityCards[i]);
    }

    //The dealer acts last.
    _opponent->setFirstAct();
    _mainPot += NextMove(&_opponent, _opponent->CheckBet(), 0);
    std::cout << std::endl;
    std::cout << "Main pot: $" << std::fixed << std::setprecision(2) << _mainPot << "\n";
    std::cout << std::endl;
    if (_dealer->HasFolded())
    {
        _opponent->Wins(_mainPot);
        EndGame();
    }
    else if (_opponent->HasFolded())
    {
        _dealer->Wins(_mainPot);
        EndGame();
    }
    else if (_dealer->IsAllIn() || _opponent->IsAllIn())
    {
        Showdown();
    }
    else
    {
        _dealer->Uncheck();
        _opponent->Uncheck();

        std::cout << std::endl;

        Showdown();
    }
}

void Poker::Showdown()
{
    while (_numCommunityCards < 5)
    {
        Card tmpCard = _deckOfCards.DrawCard();
        _communityCards[_numCommunityCards] = new Card(tmpCard.getRank(), tmpCard.getSuit());
        _dealer->setCommunityCard(tmpCard);
        _opponent->setCommunityCard(tmpCard);
        std::cout << _dealer->getName() << " places " << _communityCards[_numCommunityCards]->PrintCard() << " on the board\n";
        _numCommunityCards++;
    }

    std::cout << std::endl;
    std::cout << _dealer->getName() << " has " << _dealer->ShowHand() << "\n";
    std::cout << _opponent->getName() << " has " << _opponent->ShowHand() << "\n";
    std::cout << std::endl;

    if (_dealer->getHandRank() > _opponent->getHandRank())
    {
        _dealer->Wins(_mainPot);
    }
    else if (_dealer->getHandRank() < _opponent->getHandRank())
    {
        _opponent->Wins(_mainPot);
    }
    else if (_dealer->getHandRank() == _opponent->getHandRank())
    {
        if (_dealer->getHandHeight() > _opponent->getHandHeight())
        {
            _dealer->Wins(_mainPot);
        }
        else if (_dealer->getHandHeight() < _opponent->getHandHeight())
        {
            _opponent->Wins(_mainPot);
        }
        else  if (_dealer->getHandHeight() == _opponent->getHandHeight())
        {
            _dealer->Wins(_mainPot / 2);
            _opponent->Wins(_mainPot / 2);
        }
    }

    std::cout << std::endl;
    if (_dealer->getGameBalance() == 0)
    {
        std::cout << _dealer->getName() << " has bust out\n";
    }
    if (_opponent->getGameBalance() == 0)
    {
        std::cout << _opponent->getName() << " has bust out\n";
    }
    std::cout << std::endl;


    EndGame();
}

void Poker::EndGame() {}

//PRIVATE
void Poker::PrintCommunityCards() const
{
    std::cout << "Community cards: ";
    for (int i = 0; i < _numCommunityCards; i++)
    {
        std::cout << _communityCards[i]->PrintCard();
        if (i < _numCommunityCards - 1)
        {
            std::cout << ", ";
        }
    }
        std::cout << "\n";
}

double Poker::NextMove(PokerPlayer **actingPlayer, double highestBet, double netAmount)
{
    //End betting round if all players have checked.
    if ((*actingPlayer)->IsAllIn())
    {
        return netAmount;
    }

    //End betting round if all players have checked.
    if ((*actingPlayer)->HasChecked())
    {
        return netAmount;
    }

    //Determine the next player to act.
    PokerPlayer *nextPlayer = nullptr;
    if (*actingPlayer == _dealer)
    {
        nextPlayer = _opponent;
    }
    else
    {
        nextPlayer = _dealer;
    }

    //Determine the acting player's move.
    char action = getPlayerAction(&actingPlayer, highestBet);

    //The acting player's bet according to their move.
    double currNet = 0;

    //Recursive acting.
    if (action == 'H')
    {
        currNet = (*actingPlayer)->Check();
        return netAmount + NextMove(&nextPlayer, (*actingPlayer)->CheckBet(), currNet);
    }
    else if (action == 'B')
    {
        currNet = (*actingPlayer)->Bet();
        return netAmount + NextMove(&nextPlayer, (*actingPlayer)->CheckBet(), currNet);
    }
    else if (action == 'F')
    {
        currNet = (*actingPlayer)->Fold();
        return netAmount;
    }
    else if (action == 'C')
    {
        currNet = netAmount + (*actingPlayer)->Call(highestBet);
        return currNet;
    }
    else if (action == 'R')
    {
        currNet = (*actingPlayer)->Raise(highestBet);
        return netAmount + NextMove(&(nextPlayer), (*actingPlayer)->CheckBet(), currNet);
    }
    else if (action == 'A')
    {
        currNet = (*actingPlayer)->AllIn(highestBet);
        return netAmount + NextMove(&(nextPlayer), (*actingPlayer)->CheckBet(), currNet);
    }
}

char Poker::getPlayerAction(PokerPlayer ***actingPlayer, double highestBet)
{
    //Determine the next player to act.
    PokerPlayer *otherPlayer = nullptr;
    if (**actingPlayer == _dealer)
    {
        otherPlayer = _opponent;
    }
    else
    {
        otherPlayer = _dealer;
    }

    //The player's choice on the move they want to make.
    char userChoice;

    //Announce the name of the player whose turn it is.
    std::cout << std::endl;
    std::cout << (**actingPlayer)->getName() << "'s move.\n";
    PrintCommunityCards();
    (**actingPlayer)->PrintHoleCards();
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << (**actingPlayer)->getGameBalance() << "\n";

    //CASE: The acting player is first to act.
    if ((**actingPlayer)->IsFirstToAct())
    {
        //std::cout << "[H] Check\n"
        std::cout << "[B] Bet\n"
                  << "[F] Fold\n"
                  << "[A] All-in\n"
                  << std::endl;
        
        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'H' 
                                && toupper(userChoice) != 'B'
                                && toupper(userChoice) != 'F'
                                && toupper(userChoice) != 'A'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }

    }

    //CASE: The previous player checks.
    else if (otherPlayer->HasChecked())
    {
        //std::cout << "[H] Check\n"
        std::cout << "[B] Bet\n"
                  << "[A] All-in\n"
                  << std::endl;

        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'H'
                                && toupper(userChoice) != 'B'
                                && toupper(userChoice) != 'A'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }

    }

    //CASE: The acting player cannot raise the previous wager.
    else if ((**actingPlayer)->getGameBalance() <= highestBet)
    {
        std::cout << "[F] Fold\n"
                  << "[A] All-in\n"
                  << std::endl;

        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'F' 
                                && toupper(userChoice) != 'A'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }
        if (toupper(userChoice) == 'A')
        {
            if(otherPlayer->IsAllIn())
            {
                //otherPlayer->Return(highestBet - otherPlayer->getGameBalance());
                //_mainPot -= highestBet - otherPlayer->getGameBalance();
            }
        }
    }

    //CASE: The acting player cannot raise the previous wager because the previous player 
    //went all in.
    else if ((**actingPlayer)->getGameBalance() > highestBet && otherPlayer->IsAllIn() == true)
    {
        std::cout << "[F] Fold\n"
                  << "[C] Call\n"
                  << std::endl;

        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'F' 
                                && toupper(userChoice) != 'C'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }
    }
    
    //CASE: The acting player can raise the previous wager.
    else if ((**actingPlayer)->getGameBalance() > highestBet && otherPlayer->IsAllIn() == false)
    {
        std::cout << "[F] Fold\n"
                  << "[C] Call\n"
                  << "[R] Raise\n"
                  << "[A] All-in\n"
                  << std::endl;
        
        std::cin >> userChoice;
        while (std::cin.fail() || (toupper(userChoice) != 'F' 
                                && toupper(userChoice) != 'C'
                                && toupper(userChoice) != 'R'
                                && toupper(userChoice) != 'A'))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid input\n";
            std::cin >> userChoice;
        }
    }

    return toupper(userChoice);
}
