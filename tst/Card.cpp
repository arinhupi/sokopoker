/*
 * Card.cpp
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#include "Card.h"

#include <iostream>


static std::string suiteString[5] = {"Hertta", "Ruutu", "Risti", "Pata", "Jokeri"};
static const std::string suiteUC[5] = {"\u2665", "\u2666", "\u2663", "\u2660", "J" };
static const std::string valueStr[14] = {" A", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K"};

Card::Card() {
	// TODO Auto-generated constructor stub

}

Card::Card(int suit, int nbr) {
	if (suit < HEART || suit > JOKER || nbr < 1 || nbr > 13)
		throw std::out_of_range("Card: init values out of range");
	cardValue = suit*13 + nbr-1;
}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

void Card::setValue(int val) {
	if (val > 53)
		throw std::out_of_range("Card: setValue out of range");
	cardValue = val;
}

void Card::printCard() const {
	int maa = cardValue / 13;
	int value = cardValue % 13 + 1;
	std::cout << suiteUC[maa] << " ";
	std::cout << suiteString[maa] << " " << value << std::endl;
}


int Card::getSuit() const {
	return cardValue / 13;
}

int Card::getNumber() const {
	return cardValue % 13 + 1;
}

std::string suitName(int suit) {
	return suiteString[suit];
}

std::string Card::topRow() const {
	int suite = cardValue/13;
	return suiteUC[suite] + "  ";
}

std::string Card::midRow() const {
	int value = cardValue % 13 + 1;
	if (getSuit() == JOKER)
		return "JOK";
	else
		return valueStr[value-1] + " ";
}

std::string Card::bottomRow() const {
	int suite = cardValue / 13;
	return "  " + suiteUC[suite];
}
