/*
 * PokerHand.h
 *
 *  Created on: 20.3.2017
 *      Author: ari
 */

#ifndef POKERHAND_H_
#define POKERHAND_H_

#include <vector>
#include <map>
#include <iostream>
#include "PlayerCards.h"

#define FIVE_OF_A_KIND  	0xF00
#define STRAIGHT_FLUSH 		0xE00
#define FOUR_OF_A_KIND		0xD00
#define FULL_HOUSE			0xC00
#define FLUSH				0xB00
#define STRAIGHT  			0xA00
#define THREE_OF_A_KIND 	0x900
#define TWO_PAIRS			0x800
#define FLUSH_OF_FOUR		0x700  // soko hand
#define STRAIGHT_OF_FOUR 	0x600  // soko hand
#define PAIR				0x500
#define HIGH_CARD			0x400


class PokerHand {

public:
	static const int CARD_MAX_VALUE = 14;
	PokerHand();
	virtual ~PokerHand();
	std::string printHand() const;
	bool markCardsOfScore(const PlayerCards& plCards, std::vector<bool>& markedCard);
	int calcScoreOfHand(const PlayerCards& plCards, int firstCardIndex);
	void printScore() const;

	int getScore() const {
		return score;
	}

	void setScore(int score) {
		this->score = score;
	}

	const std::vector<bool>& getCardsOfHand() const {
		return cardsOfHand;
	}

	void setCardsOfHand(const std::vector<bool>& cardsOfHand) {
		this->cardsOfHand = cardsOfHand;
	}
	void breakupScore(int& hand, int& firstVal, int& secVal) const;

private:
	int score;
	std::vector<bool> cardsOfHand;
	static std::map<int, std::string> pHandStringFi;
	static std::map<int, std::string> pHandStringEn;

	int countSameNumber(int[], int[], int &);
	int countSameSuit(int[], const int[], int &);
	int countNumberSeq(int[], int[], int &);
	int findSeq(const int[], int, int);
	void cardsToResArrays(const PlayerCards&, int firstCardIndex, int[], int[], int &);
	void findIndexWithValue(const int[], std::vector<std::pair<int, int> >&);
	int highestCardNumber(const int numRes[], int jokers);
	void findCardsWithValue(const PlayerCards& pCards, int, std::vector<bool>&);
	void findCardsWithSuit(const PlayerCards& pCards, int, std::vector<bool>&);
	void findCardsOfStraightFour(const PlayerCards& pCards, int, std::vector<bool>&);
	int maxOfThree(int, int, int) const;
	void setAllCards(std::vector<bool>&, bool);
	std::string hexToCardVal(int) const;
	int convertToScore(int, int, int) const;
};



#endif /* POKERHAND_H_ */
