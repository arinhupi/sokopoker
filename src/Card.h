/*
 * Card.h
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#ifndef CARD_H_
#define CARD_H_

#include <string>

#define SPADE_UC "L\u2660"
#define HEART_UC "L\u2665"
#define DIAMOND_UC "L\u2666"
#define CLUB_UC "L\u2663"


class Card {
public:
	enum Suit{HEART, DIAMOND, CLUB, SPADE, JOKER};
	static const int CARD_SUITS = 4;
private:
	int cardValue; //1...52 + 2 jokers
public:
	Card();
	Card(int, int);
	virtual ~Card();
	void setValue(int);
	void printCard();
	int getSuit();
	int getNumber();
	std::string suitName(int);
	std::string topRow();
	std::string midRow();
	std::string bottomRow();
};


#endif /* CARD_H_ */
