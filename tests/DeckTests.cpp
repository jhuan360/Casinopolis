#include "gtest/gtest.h"
#include "../include/Deck.h"


class DeckTests : public ::testing::Test
{
protected:
    Deck deck1;
    Deck deck2;
    Deck deck3;
};


TEST_F(DeckTests, IsCorrectSize)
{
    //Tests that decks start out with fifty-two cards.
    EXPECT_EQ(deck1.getSize(), 52) << "ERROR: Deck does not start with 52 cards\n";
    EXPECT_EQ(deck2.getSize(), 52) << "ERROR: Deck does not start with 52 cards\n";
    EXPECT_EQ(deck3.getSize(), 52) << "ERROR: Deck does not start with 52 cards\n";
}

TEST_F(DeckTests, IsNotEmpty)
{
    //Tests that initialized decks are not empty.
    EXPECT_FALSE(deck1.IsEmpty()) << "ERROR: New deck should not be empty\n";
    EXPECT_FALSE(deck2.IsEmpty()) << "ERROR: New deck should not be empty\n";
    EXPECT_FALSE(deck3.IsEmpty()) << "ERROR: New deck should not be empty\n";
}

TEST_F(DeckTests, IsFacingDown)
{
    Card card1 = deck1.DrawCard();
    Card card2 = deck2.DrawCard();
    Card card3 = deck3.DrawCard();

    //Tests that decks start out in a face-down orientation.
    EXPECT_TRUE(card1.getRank() == Card::Rank::ACE
             && card1.getSuit() == Card::Suit::HEARTS) << "ERROR: Deck is not facing down\n";
    EXPECT_TRUE(card2.getRank() == Card::Rank::ACE
             && card1.getSuit() == Card::Suit::HEARTS) << "ERROR: Deck is not facing down\n";
    EXPECT_TRUE(card3.getRank() == Card::Rank::ACE
             && card1.getSuit() == Card::Suit::HEARTS) << "ERROR: Deck is not facing down\n";
}

TEST_F(DeckTests, AddsCard)
{
    int size1 = deck1.getSize();
    int size2 = deck2.getSize();
    int size3 = deck3.getSize();

    deck1.AddCard(Card(Card::Rank::ACE, Card::Suit::HEARTS));
    deck2.AddCard(Card(Card::Rank::ACE, Card::Suit::HEARTS));
    deck3.AddCard(Card(Card::Rank::ACE, Card::Suit::HEARTS));

    //Tests that cards can be added to the top of a deck.
    EXPECT_EQ(deck1.getSize(), size1 + 1) << "ERROR: A card could not be added to the deck\n";
    EXPECT_EQ(deck2.getSize(), size2 + 1) << "ERROR: A card could not be added to the deck\n";
    EXPECT_EQ(deck3.getSize(), size3 + 1) << "ERROR: A card could not be added to the deck\n";
}

TEST_F(DeckTests, ShufflesDeck)
{
    //Compares three non-shuffled decks. 
    //These decks should have equally ordered cards.
    EXPECT_TRUE(deck1 == deck2 
             && deck2 == deck3) << "ERROR: Unshuffled decks should have their cards orderered "
                                    "identically\n";

    deck1.RiffleShuffle();
    deck2.RiffleShuffle();
    deck3.RiffleShuffle();

    //Compares three recently shuffled decks.
    //In most cases, at least two of the decks will have differently
    //ordered cards.
    EXPECT_FALSE(deck1 == deck2 
              && deck2 == deck3) << "ERROR: Shuffled decks should have their cards orderered "
                                    "differently\n"
                                    "NOTE: This test does not account for edge cases\n";
}

TEST_F(DeckTests, IsEmpty)
{
    for (int i = 0; i < 52; i++)
    {
    deck1.DrawCard();
    deck2.DrawCard();
    deck3.DrawCard();
    }

    //Tests that fully drawn decks are empty.
    EXPECT_TRUE(deck1.IsEmpty()) << "ERROR: Fully drawn decks should be empty\n";
    EXPECT_TRUE(deck2.IsEmpty()) << "ERROR: Fully drawn decks should be empty\n";
    EXPECT_TRUE(deck3.IsEmpty()) << "ERROR: Fully drawn decks should be empty\n";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

