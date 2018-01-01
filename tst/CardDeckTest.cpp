#include "catch.hpp"
#include "CardDeck.h"


TEST_CASE("CardDeck init", "[CardDeck]"){
	CardDeck deck;
	REQUIRE(deck.getCardsInDeck() == 54);
	REQUIRE(deck.getCurPosition() ==  0);

	Card c = deck.getFirstCard();
	REQUIRE(c.getSuit() == Card::HEART);
	REQUIRE(c.getNumber() == 1);
}

TEST_CASE("CardDeckShuffle", "[CardDeck]"){
	CardDeck deck;
	deck.shuffle();
	bool deckIsShuffled = false;
	Card c;
	for (int i=0; i<10; i++){
		if (deck.getFirstCard().getNumber() != i+1){
			deckIsShuffled = true;
			break;	
		}
	}
	REQUIRE (deckIsShuffled == true);
}



/*
class CardDeck {

public:
	static const int CARDDECK_WITH_JOKERS = 54;
	static const int CARDDECK_WITHOUT_JOKERS = 52;
	CardDeck();
	CardDeck(int nrOfCards);
	virtual ~CardDeck();
	void shuffle();
	Card getFirstCard();
	void displayDeck() const;

	int getCardsInDeck() const {
		return cardsInDeck;
	}

	int getCurPosition() const {
		return curPosition;
	}
};

*/
