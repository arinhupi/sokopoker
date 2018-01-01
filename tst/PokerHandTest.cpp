#include "catch.hpp"
#include "PokerHand.h"

TEST_CASE("PokerHand getScore", "[PokerHand]"){
	PokerHand ph;
	std::vector<Card> testCards;
	PlayerCards pCards;
	int hand, firstVal, secVal;

	// five of a kind
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,3}, {Card::SPADE,3}, {Card::JOKER,2}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FIVE_OF_A_KIND);

	// straight flush
	testCards = { {Card::HEART,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::HEART,6}, {Card::HEART,7}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == STRAIGHT_FLUSH);

	// four of a kind
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,3}, {Card::SPADE,3}, {Card::HEART,7}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FOUR_OF_A_KIND);
	REQUIRE (firstVal == 3);

	// full house
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,3}, {Card::SPADE,5}, {Card::HEART,5}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FULL_HOUSE);
	REQUIRE (firstVal == 3);
	REQUIRE (secVal == 5);

	// flush
	testCards = { {Card::HEART,2}, {Card::HEART,3}, {Card::HEART,10}, {Card::HEART,7}, {Card::HEART,9}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FLUSH);

	// straight
	testCards = { {Card::HEART,2}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == STRAIGHT);
	REQUIRE (firstVal == 2);

	// three of a kind
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,3}, {Card::SPADE,6}, {Card::HEART,7}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == THREE_OF_A_KIND);
	REQUIRE (firstVal == 3);

	// two pairs
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,4}, {Card::SPADE,6}, {Card::HEART,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == TWO_PAIRS);
	REQUIRE (firstVal == 6);
	REQUIRE (secVal == 3);

	// flush of four
	testCards = { {Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,7}, {Card::HEART,9}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FLUSH_OF_FOUR);

	// straight of four
	testCards = { {Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == STRAIGHT_OF_FOUR);
	REQUIRE (firstVal == 3);

	// pair
	testCards = { {Card::HEART,1}, {Card::CLUB,3}, {Card::DIAMOND,4}, {Card::SPADE,6}, {Card::HEART,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == PAIR);
	REQUIRE (firstVal == 6);

	// highest
	testCards = { {Card::HEART,1}, {Card::CLUB,3}, {Card::DIAMOND,4}, {Card::SPADE,6}, {Card::HEART,8}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == HIGH_CARD);
	REQUIRE (firstVal == 14);

	// flush with two jokers
	testCards = { {Card::HEART,1}, {Card::JOKER,1}, {Card::JOKER,2}, {Card::HEART,6}, {Card::HEART,8}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.breakupScore(hand, firstVal, secVal);
	REQUIRE (hand == FLUSH);
	REQUIRE (firstVal == 14);

}

TEST_CASE("PokerHand markCardsOfScore", "[PokerHand]"){
	PokerHand ph;
	std::vector<Card> testCards;
	PlayerCards pCards;
	std::vector<bool> markedCards(5);

	// pair
	testCards = { {Card::HEART,1}, {Card::CLUB,3}, {Card::DIAMOND,4}, {Card::SPADE,6}, {Card::HEART,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	ph.markCardsOfScore(pCards, markedCards);
	REQUIRE(markedCards.at(0) == false);
	REQUIRE(markedCards.at(1) == false);
	REQUIRE(markedCards.at(2) == false);
	REQUIRE(markedCards.at(3) == true);
	REQUIRE(markedCards.at(4) == true);

	// three of a kind
	testCards = { {Card::JOKER,1}, {Card::CLUB,3}, {Card::DIAMOND,4}, {Card::SPADE,6}, {Card::HEART,6}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	markedCards.clear();
	ph.markCardsOfScore(pCards, markedCards);
	REQUIRE(markedCards.at(0) == true);
	REQUIRE(markedCards.at(1) == false);
	REQUIRE(markedCards.at(2) == false);
	REQUIRE(markedCards.at(3) == true);
	REQUIRE(markedCards.at(4) == true);

	// flush of four
	testCards = { {Card::HEART,2}, {Card::JOKER,1}, {Card::DIAMOND,4}, {Card::HEART,6}, {Card::HEART,10}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	markedCards.clear();
	ph.markCardsOfScore(pCards, markedCards);
	REQUIRE(markedCards.at(0) == true);
	REQUIRE(markedCards.at(1) == true);
	REQUIRE(markedCards.at(2) == false);
	REQUIRE(markedCards.at(3) == true);
	REQUIRE(markedCards.at(4) == true);

	// straight of four
	testCards = { {Card::HEART,2}, {Card::JOKER,2}, {Card::DIAMOND,4}, {Card::HEART,9}, {Card::SPADE,3}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	markedCards.clear();
	ph.markCardsOfScore(pCards, markedCards);
	REQUIRE(markedCards.at(0) == true);
	REQUIRE(markedCards.at(1) == true);
	REQUIRE(markedCards.at(2) == true);
	REQUIRE(markedCards.at(3) == false);
	REQUIRE(markedCards.at(4) == true);

	// straight of four
	testCards = { {Card::HEART,12}, {Card::JOKER,2}, {Card::DIAMOND,13}, {Card::HEART,11}, {Card::SPADE,3}};
	pCards.setCards(testCards);
	ph.calcScoreOfHand(pCards, 0);
	markedCards.clear();
	ph.markCardsOfScore(pCards, markedCards);
	REQUIRE(markedCards.at(0) == true);
	REQUIRE(markedCards.at(1) == true);
	REQUIRE(markedCards.at(2) == true);
	REQUIRE(markedCards.at(3) == true);
	REQUIRE(markedCards.at(4) == false);
}




/*
#define FIVE_OF_A_KIND  	0xF00
#define STRAIGHT_FLUSH 		0xE00
#define FOUR_OF_A_KIND		0xD00
#define FULL_HOUSE			0xC00
#define FLUSH				0xB00
#define STRAIGHT  			0xA00
#define THREE_OF_A_KIND 	0x900
#define TWO_PAIRS			0x800
#define FLUSH_OF_FOUR		0x700  // soko hand
#define STRAIGHT_OF_FOUR 	0x600  // soko hand
#define PAIR				0x500
#define HIGH_CARD			0x400


class PokerHand {

public:
	static const int CARD_MAX_VALUE = 14;
	PokerHand();
	virtual ~PokerHand();
	std::string printHand() const;
	bool markCardsOfScore(const PlayerCards& plCards, std::vector<bool>& markedCard);
	void calcScoreOfHand(const PlayerCards& plCards, int firstCardIndex);
	void printScore() const;

	int getScore() const {
		return score;
	}

	void setScore(int score) {
		this->score = score;
	}

	const std::vector<bool>& getCardsOfHand() const {
		return cardsOfHand;
	}

	void setCardsOfHand(const std::vector<bool>& cardsOfHand) {
		this->cardsOfHand = cardsOfHand;
	}
	void breakupScore(int& hand, int& firstVal, int& secVal) const;

};
*/
