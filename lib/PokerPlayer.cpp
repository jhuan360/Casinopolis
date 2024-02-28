#include <iomanip>
#include <iostream>
#include <limits>
#include "../include/PokerPlayer.h"


PokerPlayer::PokerPlayer(std::string name, int balance, double gameBalance) 
: Player(balance, name) 
{
    _gameBalance = gameBalance;
}

PokerPlayer::~PokerPlayer() 
{
    //Deallocate memory for the individual cards.
    delete _cards[0];    
    delete _cards[1];    
    delete _cards[2];    
    delete _cards[3];    
    delete _cards[4];    
    delete _cards[5];    
    delete _cards[6];    

    //Deallocate memory for the array of cards.
    delete[] _cards;

    //Deallocate memory for the array of community cards.
    delete[] _communityCards;

    //Deallocate memory for the array of hole cards.
    delete[] _holeCards;
}

double PokerPlayer::BlindBet(double cost)
{
    double blindBet = cost;

    //The player can cover the cost of the blind bet without going all-in.
    if (_gameBalance > cost) {
        _gameBalance -= cost;
        _currBet += cost;
    }  
    //The player must go all-in.
    else  
    {
        _currBet += _gameBalance;
        blindBet = _gameBalance;
        _gameBalance = 0;
    }

    return blindBet;
}

int PokerPlayer::getHandRank() const
{
    //Sort the card ranks in the player's hand by index.
    int rankIndices[13] {0};
    for (int i = 0; i < _numCards; i++)
    {
        int rankIndex = static_cast<int>(_cards[i]->getRank());
        rankIndices[rankIndex - 1] += 1;
    }
    
    //Find the most amount of times that a card rank is repeated.
    int rankDegree = 0;
    for (int i = 0; i < 13; i++)
    {
        if (rankDegree < rankIndices[i])
        {
            rankDegree = rankIndices[i];
        }
    }

    //Check for a straight hand.
    int numStraight = 0;
    //Additionally, determine whether a straight hand is royal.
    bool isRoyal = false;
    for (int i = 0; i < 13; i++)
    {
        if (rankIndices[i] > 0)
        {
            numStraight++;
            if (i == 12 && numStraight == 4)
            {
                if (rankIndices[0] > 0)
                {
                    numStraight++;
                    isRoyal = true;
                }
            }
        }
        else
        {
            numStraight = 0;
        }
    }

    //Calculate the amount of pairs present in the player's hand.
    int numPairs = 0;
    for (int i = 0; i < 13; i++)
    {
        if (!(rankIndices[i] % 2))
        {
            numPairs += rankIndices[i] / 2;
        }
    }

    //Sort the card suits in the player's hand by index.
    int suitIndices[4] {0};
    for (int i = 0; i < _numCards; i++)
    {
        int suitIndex = static_cast<int>(_cards[i]->getSuit());
        suitIndices[suitIndex - 1] += 1;
    }

    //Find the most amount of times that a card suit is repeated.
    int suitDegree = 1;
    for (int i = 0; i < 4; i++)
    {
        if (suitDegree < suitIndices[i])
        {
            suitDegree = suitIndices[i];
        }
    }

    //Default to the lowest hand rating.
    int rating = 0;

    //Assign hand ratings in a weakest-to-strongest direction.
    if (_numCards > 0)
    {
        rating = 1;
    }
    if (numPairs == 1)
    {
        rating = 2;
    }
    if (numPairs >= 2)
    {
        rating = 3;
    }
    if (rankDegree == 3)
    {
        rating = 4;
    }
    if (numStraight == 5)
    {
        rating = 5;
    }
    if (suitDegree == 5)
    {
        rating = 6;
    }
    if (rankDegree == 3 && numPairs >= 1)
    {
        rating = 7;
    }
    if (rankDegree == 4)
    {
        rating = 8;
    }
    if (suitDegree == 5 && numStraight == 5)
    {
        rating = 9;
    }
    if (isRoyal && suitDegree == 5)
    {
        rating = 10;
    }

    return rating;
}

void PokerPlayer::SortCardsByRank()
{
    for (int i = 1; i < _numCards; i++)
    {
        Card *tmpCard = _cards[i];
        int j = i - 1;
 
        while (j >= 0 
            && static_cast<int>(_cards[j]->getRank()) > static_cast<int>(tmpCard->getRank()))
        {
            _cards[j + 1] = _cards[j];
            j = j - 1;
        }
        _cards[j + 1] = tmpCard;
    }
}

void PokerPlayer::SortCardsBySuit()
{
    for (int i = 1; i < _numCards; i++)
    {
        Card *tmpCard = _cards[i];
        int j = i - 1;
 
        while (j >= 0 
            && static_cast<int>(_cards[j]->getSuit()) > static_cast<int>(tmpCard->getSuit()))
        {
            _cards[j + 1] = _cards[j];
            j = j - 1;
        }
        _cards[j + 1] = tmpCard;
    }
}

int PokerPlayer::getHandHeight()
{
    if (getHandRank() == 10)
    {
        return 14;
    }
    if (getHandRank() == 9)
    {
        SortCardsByRank();

        int high = 0;
        for (int i = 0; i < _numCards - 3; i++)
        {
            if (i < _numCards - 4)
            {
                if (static_cast<int>(_cards[i]->getRank()) == static_cast<int>(_cards[i + 1]->getRank()) - 1
                 && static_cast<int>(_cards[i + 1]->getRank()) == static_cast<int>(_cards[i + 2]->getRank()) - 1
                 && static_cast<int>(_cards[i + 2]->getRank()) == static_cast<int>(_cards[i + 3]->getRank()) - 1
                 && static_cast<int>(_cards[i + 3]->getRank()) == static_cast<int>(_cards[i + 4]->getRank()) - 1)
                {
                    if (_cards[i]->getSuit() == _cards[i + 1]->getSuit()
                     && _cards[i + 1]->getSuit() == _cards[i + 2]->getSuit()
                     && _cards[i + 2]->getSuit() == _cards[i + 3]->getSuit()
                     && _cards[i + 3]->getSuit() == _cards[i + 4]->getSuit())
                    {
                        high = static_cast<int>(_cards[i + 4]->getRank());
                    }
                }
            }
            if (i == _numCards - 4)
            {
                if ((_cards[i]->getRank() == Card::Rank::TEN)
                 && (_cards[i + 1]->getRank() == Card::Rank::JACK)
                 && (_cards[i + 2]->getRank() == Card::Rank::QUEEN)
                 && (_cards[i + 3]->getRank() == Card::Rank::KING)
                 && (_cards[0]->getRank() == Card::Rank::ACE))
                {
                    if (_cards[i]->getSuit() == _cards[i + 1]->getSuit()
                     && _cards[i + 1]->getSuit() == _cards[i + 2]->getSuit()
                     && _cards[i + 2]->getSuit() == _cards[i + 3]->getSuit())
                    {
                        int j = _numCards - 4;
                        while (j > 0)
                        {
                            if (_cards[j - 1]->getRank() == Card::Rank::ACE
                             && _cards[j - 1]->getSuit() == _cards[i]->getSuit())
                             {
                                return 14;
                             }
                             j--;
                        }
                    }
                }
            }
        }
        return high;
    }
    if (getHandRank() == 8)
    {
        SortCardsByRank();

        for (int i = 0; i < _numCards - 3; i++)
        {
            if (_cards[i]->getRank() == _cards[i + 3]->getRank())
            {
                if (_cards[i]->getRank() == Card::Rank::ACE)
                {
                    return 14;
                }
                return static_cast<int>(_cards[i]->getRank());
            }
        }
    }
    if (getHandRank() == 7)
    {
        SortCardsByRank();

        for (int i = 0; i < _numCards - 2; i++)
        {
            if (_cards[i]->getRank() == _cards[i + 2]->getRank())
            {
                if (_cards[i]->getRank() == Card::Rank::ACE)
                {
                    return 14;
                }
                return static_cast<int>(_cards[i]->getRank());
            }
        }
    }
    if (getHandRank() == 6)
    {
        SortCardsBySuit();

        int high = 0;
        for (int i = 0; i < _numCards - 4; i++)
        {
            int j = i;
            if ((_cards[i]->getSuit()) == _cards[i + 4]->getSuit())
            {
                for (int j = i; j <= i + 4; j++)
                {
                    if (_cards[j]->getRank() == Card::Rank::ACE)
                    {
                        return 14;
                    }
                    if (static_cast<int>(_cards[j]->getRank()) > high)
                    {
                        high = static_cast<int>(_cards[j]->getRank());
                    }
                }
            }
        }
        return high;
    }
    if (getHandRank() == 5)
    {
        SortCardsByRank();

        int high = 0;
        for (int i = 0; i < _numCards - 3; i++)
        {
            if (i < _numCards - 4)
            {
                if (static_cast<int>(_cards[i]->getRank()) == static_cast<int>(_cards[i + 1]->getRank()) - 1
                 && static_cast<int>(_cards[i + 1]->getRank()) == static_cast<int>(_cards[i + 2]->getRank()) - 1
                 && static_cast<int>(_cards[i + 2]->getRank()) == static_cast<int>(_cards[i + 3]->getRank()) - 1
                 && static_cast<int>(_cards[i + 3]->getRank()) == static_cast<int>(_cards[i + 4]->getRank()) - 1)
                {
                    high = static_cast<int>(_cards[i + 4]->getRank());
                }
            }
            if (i == _numCards - 4)
            {
                if ((_cards[i]->getRank() == Card::Rank::TEN)
                 && (_cards[i + 1]->getRank() == Card::Rank::JACK)
                 && (_cards[i + 2]->getRank() == Card::Rank::QUEEN)
                 && (_cards[i + 3]->getRank() == Card::Rank::KING)
                 && (_cards[0]->getRank() == Card::Rank::ACE))
                {
                    return 14;
                }
            }
        }
        return high;
    }
    if (getHandRank() == 4)
    {
        SortCardsByRank();

        int high = 0;
        for (int i = 0; i < _numCards - 2; i++)
        {
            if (_cards[i]->getRank() == _cards[i + 2]->getRank())
            {
                if (_cards[i]->getRank() == Card::Rank::ACE)
                {
                    return 14;
                }
                if (static_cast<int>(_cards[i]->getRank()) > high)
                {
                    high = static_cast<int>(_cards[i]->getRank());
                }
            }
        }
        return high;
    }
    if (getHandRank() == 3)
    {
        SortCardsByRank();

        int high = 0;
        for (int i = 0; i < _numCards - 1; i++)
        {
            if (_cards[i]->getRank() == _cards[i + 1]->getRank())
            {
                if (_cards[i]->getRank() == Card::Rank::ACE)
                {
                    return 14;
                }
                if (static_cast<int>(_cards[i]->getRank()) > high)
                {
                    high = static_cast<int>(_cards[i]->getRank());
                }
            }
        }      
        return high;
    }
    if (getHandRank() == 2)
    {
        SortCardsByRank();

        for (int i = 0; i < _numCards - 1; i++)
        {
            if (_cards[i]->getRank() == _cards[i + 1]->getRank())
            {
                if (_cards[i]->getRank() == Card::Rank::ACE)
                {
                    return 14;
                }
                return static_cast<int>(_cards[i]->getRank());
            }
        }
    }
    if (getHandRank() == 1)
    {
        SortCardsByRank();

        if (_cards[0]->getRank() == Card::Rank::ACE)
        {
            return 14;
        }
        return static_cast<int>(_cards[_numCards - 1]->getRank());
    }
    if (getHandRank() == 0)
    {
        return 0;
    }
}

std::string PokerPlayer::ShowHandRank() const
{
    switch(getHandRank())
    {
        case 0:
            return "Empty Hand";
            break;
        case 1:
            return "";
            break;
		case 2:
			return "Pair";
			break;
		case 3:
            return "Two Pair";
            break;
		case 4:
			return "Three of a Kind";
			break;
		case 5:
            return "Straight";
            break;
		case 6:
			return "Flush";
			break;
		case 7:
            return "Full House";
            break;
		case 8:
			return "Four of a Kind";
			break;
		case 9:
            return "Straight Flush";
            break;
		case 10:
			return "Royal Flush";
			break;
    }
}

std::string PokerPlayer::ShowHandHeight()
{
    switch(getHandHeight())
    {
        case 0:
            return "";
            break;
        case 1:
            return "Ace High";
            break;
		case 2:
			return "Two High";
			break;
		case 3:
            return "Three High";
            break;
		case 4:
			return "Four High";
			break;
		case 5:
            return "Five High";
            break;
		case 6:
			return "Six High";
			break;
		case 7:
            return "Seven High";
            break;
		case 8:
			return "Eight High";
			break;
		case 9:
            return "Nine High";
            break;
		case 10:
			return "Ten High";
			break;
		case 11:
			return "Jack High";
			break;
		case 12:
			return "Queen High";
			break;
		case 13:
			return "King High";
			break;
		case 14:
			return "Ace High";
			break;
    }
}

std::string PokerPlayer::ShowHand()
{
    return ShowHandHeight() + " " + ShowHandRank();
}

void PokerPlayer::PrintHoleCards() const
{

    std::cout << _playerName << "'s cards: ";
    for (int i = 0; i < _numHoleCards; i++)
    {
        std::cout << _holeCards[i]->PrintCard();
        if (i == 0)
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << "\n";
        }
    }
}

double PokerPlayer::getGameBalance() const
{
    return _gameBalance;
}

void PokerPlayer::setHoleCard(Card holeCard)
{
    std::cout << getName() << " receives " << holeCard.PrintCard() << "\n";

    if (_numHoleCards < 2)
    {
        _holeCards[_numHoleCards] = new Card(holeCard.getRank(), holeCard.getSuit());
        _numHoleCards++;

        _cards[_numCards] = _holeCards[_numHoleCards - 1];
        _numCards++;
    }

}

void PokerPlayer::setCommunityCard(Card communityCard)
{
    if (_numCommunityCards < 5)
    {
        _communityCards[_numCommunityCards] = new Card(communityCard.getRank(), communityCard.getSuit());
        _numCommunityCards++;

        _cards[_numCards] = _communityCards[_numCommunityCards - 1];
        _numCards++;
    }
}

void PokerPlayer::setFirstAct()
{
    _firstToAct = true;
}

bool PokerPlayer::IsFirstToAct() const
{
    return _firstToAct;
}

void PokerPlayer::SetFirstAct()
{
    _firstToAct = true;
}

bool PokerPlayer::HasChecked() const
{
    return _checked;
}

void PokerPlayer::Uncheck()
{
    _checked = false;
}

bool PokerPlayer::HasFolded() const
{
    return _folded;
}

bool PokerPlayer::IsAllIn() const
{
    return _allIn;
}

double PokerPlayer::CheckBet() const
{
    return _currBet;
}

double PokerPlayer::Check()
{
    _checked = true;
    std::cout << getName() << " checked\n";    
    _firstToAct = false;

    return 0;
}

double PokerPlayer::Fold()
{
    _folded = true;
    std::cout << getName() << " folded\n";
    _firstToAct = false;
    
    return 0;
}

double PokerPlayer::Call(double currBet)
{
    double userCall = currBet - _currBet;
    _gameBalance -= userCall;
    std::cout << getName() << " called\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";

    return userCall;
}

double PokerPlayer::Bet()
{
    std::cout << "Enter an amount: ";

    double userBet;
    std::cin >> userBet;
    while (std::cin.fail() || ((userBet <= 0)
                             || (userBet > _gameBalance)))
    {
        if (std::cin.fail())
        {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> userBet;
    }

    _currBet += userBet;
    _firstToAct = false;
    if (userBet == _gameBalance)
    {
        _allIn = true;
        std::cout << getName() << " went all-in\n";
        _gameBalance = 0;
        std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";
        return userBet;
    }
    _gameBalance -= userBet;
    std::cout << getName() << " bet $" << userBet << "\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";
    return userBet;
}

double PokerPlayer::Raise(double currBet)
{
    std::cout << "Enter an amount: ";

    double userRaise;
    std::cin >> userRaise;
    while (std::cin.fail() || ((userRaise + _currBet <= currBet)
                             || (userRaise > _gameBalance)))
    {
        if (std::cin.fail())
        {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> userRaise;
    }

    _currBet += userRaise;
    if (userRaise == _gameBalance)
    {
        _allIn = true;
        std::cout << getName() << " went all-in\n";
        _gameBalance = 0;
        return userRaise;
    }
    _gameBalance -= userRaise;
    std::cout << getName() << " raised $" << (_currBet - currBet) << "\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";
    return userRaise;
}

double PokerPlayer::AllIn(double currBet)
{
    double allIn = _gameBalance;
    _currBet += _gameBalance;
    _gameBalance = 0;
    std::cout << getName() << " went all-in\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";

    _firstToAct = false;
    _allIn = true;
    
    return allIn;
}

void PokerPlayer::Return(double refund)
{
    _gameBalance += refund;
    std::cout << getName() << " was refunded $" << refund << "\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";
}

void PokerPlayer::Wins(double amount)
{
    _gameBalance += amount;
    std::cout << getName() << " wins $" << amount << "\n";
    std::cout << "Remaining game balance: $" << std::fixed << std::setprecision(2) << _gameBalance << "\n";
}