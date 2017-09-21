/*
 * PlayerCards.cpp
 *
 *  Created on: 18.3.2017
 *      Author: ari
 */

#include "PlayerCards.h"
#include "PokerHand.h"

PlayerCards::PlayerCards() {
	// TODO Auto-generated constructor stub

}

PlayerCards::~PlayerCards() {
	// TODO Auto-generated destructor stub
}

void PlayerCards::addToDeck(Card card) {
	pCards.push_back(card);
}

void PlayerCards::dispCards() {
	for (std::vector<Card>::iterator i = pCards.begin(); i != pCards.end(); i++){
		i->printCard();
	}
	std::cout << "\n";
}

void PlayerCards::dispCards2(){
	std::string frameString = "+";
	for (unsigned int i=0; i < pCards.size(); i++)
		frameString += "---+";
	std::cout << frameString << "\n";

	for (std::vector<Card>::iterator i = pCards.begin(); i != pCards.end(); i++)
		std::cout << "|" << i->topRow();
	std::cout << "|\n";

	for (std::vector<Card>::iterator i = pCards.begin(); i != pCards.end(); i++)
		std::cout << "|" << i->midRow();
	std::cout << "|\n";

	for (std::vector<Card>::iterator i = pCards.begin(); i != pCards.end(); i++)
		std::cout << "|" << i->bottomRow();
	std::cout << "|\n";
	std::cout << frameString << "\n";
}

void PlayerCards::dispCards3(bool firstHidden){
	std::string frameString = "+";
	for (unsigned int i=0; i < pCards.size(); i++)
		frameString += "---+";
	std::cout << frameString << "\n";

	for (unsigned int i=0; i < pCards.size(); i++)
		std::cout << "|" << ((firstHidden && i == 0) ? "   " : pCards.at(i).topRow());
	std::cout << "|\n";

	for (unsigned int i=0; i < pCards.size(); i++)
		std::cout << "|" << ((firstHidden && i == 0) ? " ? " : pCards.at(i).midRow());
	std::cout << "|\n";

	for (unsigned int i=0; i < pCards.size(); i++)
		std::cout << "|" << ((firstHidden && i == 0) ? "   " : pCards.at(i).bottomRow());
	std::cout << "|\n";

	std::cout << frameString << "\n";
}


void PlayerCards::changeCard(CardDeck& deck, int cardNr) {
	pCards.at(cardNr) = deck.getFirstCard();
}

void PlayerCards::resetCards() {
	pCards.clear();
}

