#include "gtest/gtest.h"
#include "../include/Card.h"


class CardTests : public ::testing::Test
{
protected:
    Card card1 = Card(Card::Rank::JACK, Card::Suit::SPADES);
    Card card2 = Card(Card::Rank::QUEEN, Card::Suit::DIAMONDS);
    Card card3 = Card(Card::Rank::KING, Card::Suit::CLUBS);
    Card card4 = Card(Card::Rank::ACE, Card::Suit::HEARTS);
};


TEST_F(CardTests, ReturnsRank)
{
    EXPECT_EQ(card1.getRank(), Card::Rank::JACK) << "ERROR: Card rank has unexpectedly changed\n";
    EXPECT_EQ(card2.getRank(), Card::Rank::QUEEN) << "ERROR: Card rank has unexpectedly changed\n";
    EXPECT_EQ(card3.getRank(), Card::Rank::KING) << "ERROR: Card rank has unexpectedly changed\n";
    EXPECT_EQ(card4.getRank(), Card::Rank::ACE) << "ERROR: Card rank has unexpectedly changed\n";
}

TEST_F(CardTests, ReturnsSuit)
{
    EXPECT_EQ(card1.getSuit(), Card::Suit::SPADES) << "ERROR: Card suit has unexpectedly changed\n";
    EXPECT_EQ(card2.getSuit(), Card::Suit::DIAMONDS) << "ERROR: Card suit has unexpectedly changed\n";
    EXPECT_EQ(card3.getSuit(), Card::Suit::CLUBS) << "ERROR: Card suit has unexpectedly changed\n";
    EXPECT_EQ(card4.getSuit(), Card::Suit::HEARTS) << "ERROR: Card suit has unexpectedly changed\n";
}

TEST_F(CardTests, PrintsCard)
{
    EXPECT_EQ(card1.PrintCard(), "Jack of Spades") << "ERROR: Incorrect card printed out\n";
    EXPECT_EQ(card2.PrintCard(), "Queen of Diamonds") << "ERROR: Incorrect card printed out\n";
    EXPECT_EQ(card3.PrintCard(), "King of Clubs") << "ERROR: Incorrect card printed out\n";
    EXPECT_EQ(card4.PrintCard(), "Ace of Hearts") << "ERROR: Incorrect card printed out\n";
}

TEST_F(CardTests, ComparesCards)
{
    Card card1Copy = card1;
    Card card2Copy = card2;
    Card card3Copy = card3;
    Card card4Copy = card4;

    EXPECT_TRUE(card1Copy == card1) << "ERROR: Card does not match a copy of itself\n";
    EXPECT_TRUE(card2Copy == card2) << "ERROR: Card does not match a copy of itself\n";
    EXPECT_TRUE(card3Copy == card3) << "ERROR: Card does not match a copy of itself\n";
    EXPECT_TRUE(card4Copy == card4) << "ERROR: Card does not match a copy of itself\n";
    
    EXPECT_FALSE(card1 == card2  
              || card1 == card3 
              || card1 == card4) << "ERROR: Unique cards should not match\n";
    EXPECT_FALSE(card2 == card3  
              || card2 == card4 
              || card2 == card1) << "ERROR: Unique cards should not match\n";
    EXPECT_FALSE(card3 == card4  
              || card3 == card1 
              || card3 == card2) << "ERROR: Unique cards should not match\n";
    EXPECT_FALSE(card4 == card1  
              || card4 == card2 
              || card4 == card3) << "ERROR: Unique cards should not match\n";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

