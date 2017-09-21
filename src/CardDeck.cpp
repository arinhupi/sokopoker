/*
 * CardDeck.cpp
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#include "CardDeck.h"
#include <iostream>
#include <algorithm>



CardDeck::CardDeck(): curPosition(0) {
	Card card;
	cardsInDeck = CARDDECK_WITH_JOKERS;
	for (int i=0; i<cardsInDeck; i++){
		card.setValue(i);
		cardDeck.push_back(card);
	}
}

CardDeck::CardDeck(int nrOfCards): curPosition(0) {
	if (nrOfCards != CARDDECK_WITH_JOKERS && nrOfCards != CARDDECK_WITHOUT_JOKERS){
		std::cout << "CardDeck constructor: Wrong number of cards, exiting...";
		exit(EXIT_FAILURE);
	}
	Card card;
	cardsInDeck = nrOfCards;
	for (int i=0; i<cardsInDeck; i++){
		card.setValue(i);
		cardDeck.push_back(card);
	}
}

CardDeck::~CardDeck() {
	// TODO Auto-generated destructor stub
}


void CardDeck::shuffle(){
	srand (time(NULL));
	random_shuffle(cardDeck.begin(), cardDeck.end());
	curPosition = 0;
}

void CardDeck::displayDeck() {
	std::cout << "curTop now: " << curPosition << std::endl;
	for (int i=curPosition; i<cardsInDeck; i++)
		cardDeck.at(i).printCard();

}

Card CardDeck::getFirstCard() {
	Card card;
	try{
		card = cardDeck.at(curPosition++);
	}
	catch(...) {
		std::cout << "ERROR: End of card deck !!!\n";
		throw;
	}
	return card;
}

void CardDeck::swapCards(int a, int b) {
	Card tmpCard = cardDeck.at(a);
	cardDeck.at(a) = cardDeck.at(b);
	cardDeck.at(b) = tmpCard;
}


