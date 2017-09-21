/*
 * PlayerCards.h
 *
 *  Created on: 18.3.2017
 *      Author: ari
 */

#ifndef PLAYERCARDS_H_
#define PLAYERCARDS_H_

#include <vector>
#include <iostream>
#include "Card.h"
//#include "PokerHand.h"
#include "CardDeck.h"



class PlayerCards {
	std::vector<Card> pCards;
public:
	PlayerCards();
	virtual ~PlayerCards();
	void addToDeck(Card card);
	void dispCards();
	void dispCards2();
	void dispCards3(bool firstHidden);
	void changeCard(CardDeck& deck, int cardNr);
	void resetCards();
	void setTestDeck(const std::vector<int> testCards);
	const std::vector<Card>& getCards() const {
		return pCards;
	}

	void setCards(const std::vector<Card>& cards) {
		pCards = cards;
	}
	typedef std::vector<Card>::iterator PCardIter;


};

#endif /* PLAYERCARDS_H_ */
