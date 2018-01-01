#include "catch.hpp"
#include "PlayerCards.h"

TEST_CASE("PlayerCards addToDeck-reset", "[PlayerCards]"){
	CardDeck deck;
	PlayerCards pc;
	REQUIRE(pc.getCardAmount() == 0);
	for (int i=0; i<5; i++){
	 	Card c = deck.getFirstCard();
		pc.addToDeck(c);
	}
	REQUIRE(pc.getCardAmount() == 5);
	pc.resetCards();
	REQUIRE(pc.getCardAmount() == 0);
}

TEST_CASE("PlayerCards setCards", "[PlayerCards]"){
	PlayerCards pc;
	std::vector<Card> testCards =  { {Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,7}, {Card::HEART,9}};
	pc.setCards(testCards);

	REQUIRE(pc.getCardAmount() == 5);
	REQUIRE(pc.getCardAt(2).getNumber() == 4);
}

TEST_CASE("PlayerCards changeCard", "[PlayerCards]"){
	CardDeck deck;
	PlayerCards pc;
 	Card c1 = deck.getFirstCard();
	pc.addToDeck(c1);
	pc.changeCard(deck, 0);
	Card c2 = pc.getCardAt(0);
	REQUIRE(c1.getNumber() != c2.getNumber());
}


/*
class PlayerCards {
public:
	PlayerCards();
	virtual ~PlayerCards();
	void addToDeck(Card card);
	void dispCards();
	void dispCards2();
	void dispCards3(bool firstHidden) const;
	void changeCard(CardDeck& deck, int cardNr);
	void resetCards();
	int getCardAmount() const;
	Card getCardAt(int cardNr) const;	
	const std::vector<Card>& getCards() const {
		return pCards;
	}

	void setCards(const std::vector<Card>& cards) {
		pCards = cards;
	}
	typedef std::vector<Card>::iterator PCardIter;
};
*/
