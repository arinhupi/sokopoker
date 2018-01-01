#include "catch.hpp"
#include "Card.h"


#define SPADE_UC "L\u2660"
#define HEART_UC "L\u2665"
#define DIAMOND_UC "L\u2666"
#define CLUB_UC "L\u2663"

TEST_CASE("Card init", "[Card]"){
	Card card1;
	card1.setValue(0);
	REQUIRE(card1.getSuit() == Card::HEART);

	REQUIRE_THROWS(card1.setValue(54));
}

TEST_CASE("Card init with params", "[Card]"){
	Card card(Card::HEART, 1);
	REQUIRE(card.getSuit() == Card::HEART);
	REQUIRE(card.getNumber() == 1);

	Card card2(Card::DIAMOND, 7);
	REQUIRE(card2.getSuit() == Card::DIAMOND);
	REQUIRE(card2.getNumber() == 7);

	Card card3(Card::JOKER, 2);
	REQUIRE(card3.getSuit() == Card::JOKER);
	REQUIRE(card3.getNumber() == 2);

}

/*
class Card {
public:
	enum Suit{HEART, DIAMOND, CLUB, SPADE, JOKER};
	static const int CARD_SUITS = 4;
	Card();
	Card(int, int);
	virtual ~Card();
	void setValue(int);
	void printCard() const;
	int getSuit() const;
	int getNumber() const;
	std::string suitName(int) const;
	std::string topRow() const;
	std::string midRow() const;
	std::string bottomRow() const;
private:
	int cardValue; //1...52 + 2 jokers

};

*/
