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
#include "CardDeck.h"


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

private:
	std::vector<Card> pCards;
};

#endif /* PLAYERCARDS_H_ */
