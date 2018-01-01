/*
 * CardDeck.h
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#ifndef CARDDECK_H_
#define CARDDECK_H_

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Card.h"



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

private:
	std::vector<Card> cardDeck;
	int cardsInDeck;
	int curPosition;

	void swapCards(int, int);
};



#endif /* CARDDECK_H_ */
