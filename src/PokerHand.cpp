/*
 * PokerHand.cpp
 *
 *  Created on: 20.3.2017
 *      Author: ari
 */

#include <stdio.h>
#include <string>
#include "PokerHand.h"

std::map<int, std::string> PokerHand::pHandStringFi =
		{ 		{FIVE_OF_A_KIND, "vitoset"},
				{STRAIGHT_FLUSH, "värisuora"},
				{FOUR_OF_A_KIND, "neloset"},
				{FULL_HOUSE, "täyskäsi"},
				{FLUSH, "väri"},
				{STRAIGHT, "suora"},
				{THREE_OF_A_KIND, "kolmoset"},
				{TWO_PAIRS, "kaksi paria"},
				{FLUSH_OF_FOUR, "neljän väri"},
				{STRAIGHT_OF_FOUR, "neljän suora"},
				{PAIR, "pari"},
				{HIGH_CARD, "korkein kortti"}
		};

std::map<int, std::string> PokerHand::pHandStringEn =
		{ 		{FIVE_OF_A_KIND, "five of a kind"},
				{STRAIGHT_FLUSH, "straight flush"},
				{FOUR_OF_A_KIND, "four of a kind"},
				{FULL_HOUSE, "full house"},
				{FLUSH, "flush"},
				{STRAIGHT, "straight"},
				{THREE_OF_A_KIND, "three of a kind"},
				{TWO_PAIRS, "two pairs"},
				{FLUSH_OF_FOUR, "flush of four"},
				{STRAIGHT_OF_FOUR, "straight of four"},
				{PAIR, "pair"},
				{HIGH_CARD, "high card"}
		};


PokerHand::PokerHand(): score(0) {
}

PokerHand::~PokerHand() {
	// TODO Auto-generated destructor stub
}


std::string PokerHand::printHand() {
	std::string scoreStr;
	int handVal, firstVal, secVal;
	breakupScore(handVal, firstVal, secVal);

	scoreStr = pHandStringEn[handVal];
	scoreStr += " / " + hexToCardVal(firstVal);
	if (handVal >= TWO_PAIRS && secVal > 0)
		scoreStr += " / " + hexToCardVal(secVal);
	std::cout << scoreStr << std::endl;
	return scoreStr;
}


void PokerHand::printScore(){
	printf("Score is: %X | ", score);

	for (bool found : cardsOfHand)
		std::cout << (found ? "x" : "-");
	printf("\n");
}


int PokerHand::countSameNumber(int suitResults[], int numberResults[], int& jokers) {
	std::vector<std::pair<int, int> > resPair;
	findIndexWithValue(numberResults, resPair);

	resPair.at(0).first += jokers;
	int sameNumMax = resPair.at(0).first;
	int sameNumSecond = resPair.size() > 1 ? resPair.at(1).first : 0;

	if (sameNumMax == 5)
		return convertToScore(FIVE_OF_A_KIND, resPair.at(0).second, 0);
	else if (sameNumMax == 4)
		return convertToScore(FOUR_OF_A_KIND, resPair.at(0).second, 0);
	else if (sameNumMax == 3){
		if (sameNumSecond == 2)
			return convertToScore(FULL_HOUSE, resPair.at(0).second, resPair.at(1).second);
		else
			return convertToScore(THREE_OF_A_KIND, resPair.at(0).second, 0);
	}
	else if (sameNumMax == 2){
		if (sameNumSecond == 2)
			return convertToScore(TWO_PAIRS, resPair.at(0).second, resPair.at(1).second);
		else if (sameNumSecond == 1)
			return convertToScore(PAIR, resPair.at(0).second, resPair.at(1).second);
		else // can happen in sökö checking
			return convertToScore(PAIR, resPair.at(0).second, 0);
	}
	else {
		if (resPair.size() > 1)
			return convertToScore(HIGH_CARD, resPair.at(0).second, resPair.at(1).second);
		else // in sökö checking
			return convertToScore(HIGH_CARD, resPair.at(0).second, 0);
	}

}

int PokerHand::countSameSuit(int suitResults[], const int numberResults[], int& jokers) {
	int bestRes = 0;
	for (int i=0; i<Card::CARD_SUITS; i++){
		if (suitResults[i] >= bestRes){
			bestRes = suitResults[i];
		}
	}
	bestRes += jokers;
	if (bestRes == 5)
		return convertToScore(FLUSH, highestCardNumber(numberResults, jokers), 0);
	else if (bestRes == 4)
		return convertToScore(FLUSH_OF_FOUR, highestCardNumber(numberResults, jokers), 0);
	else
		return 0;
}

int PokerHand::countNumberSeq(int suitResults[], int numberResults[], int& jokers){
	int bestRes = 0, bestNumber;
	for (int i=1; i<=CARD_MAX_VALUE; i++){
		int curSec = findSeq(numberResults, i, jokers);
		if (curSec >= bestRes){
			bestRes = curSec;
			bestNumber = i;
		}
	}
	if (bestRes == 5)
		return convertToScore(STRAIGHT, bestNumber, 0);
	else if (bestRes == 4)
		return convertToScore(STRAIGHT_OF_FOUR, bestNumber, 0);
	else
		return 0;
}

int PokerHand::findSeq(const int nres[], int index, int jokers){
	int seqLen = 0;
	for (unsigned int i=index; i<15; i++){
		if (nres[i] >= 1)
			seqLen++;
		else if (jokers--)
			seqLen++;
		else
			break;
	}
	return seqLen;
}

void PokerHand::cardsToResArrays(const PlayerCards& pCards, int firstCardIndex, int suitRes[], int numRes[], int& jokers) {
	for (unsigned int i=firstCardIndex; i<pCards.getCards().size(); i++){
		Card c = pCards.getCards().at(i);
		int suit = c.getSuit();
		if (suit == Card::JOKER)
			jokers++;
		else {
			suitRes[suit]++;
			int cardNumber = c.getNumber();
			numRes[cardNumber]++;
			if (cardNumber == 1)
				numRes[CARD_MAX_VALUE]++;
		}
	}
}


void PokerHand::findIndexWithValue(const int numArr[], std::vector<std::pair<int, int> > &resVec) {
	for (int value=4; value >= 1; value--){
		for (int j=CARD_MAX_VALUE; j>1; j--){
			if (numArr[j] == value)
				resVec.push_back(std::make_pair(value, j));
		}
	}
}

bool PokerHand::markCardsOfScore(const PlayerCards& pCards, int score, std::vector<bool>& markedCard) {
	int handVal, firstVal, secVal;
	breakupScore(handVal, firstVal, secVal);
	markedCard.assign(pCards.getCards().size(), false);

	switch (handVal){
	case FOUR_OF_A_KIND:
		findCardsWithValue(pCards, firstVal, markedCard);
		break;
	case THREE_OF_A_KIND:
		findCardsWithValue(pCards, firstVal, markedCard);
		break;
	case TWO_PAIRS:
		findCardsWithValue(pCards, firstVal, markedCard);
		findCardsWithValue(pCards, secVal, markedCard);
		break;
	case PAIR:
		findCardsWithValue(pCards, firstVal, markedCard);
		break;
	case HIGH_CARD:
		findCardsWithValue(pCards, firstVal, markedCard);
		break;
	case FIVE_OF_A_KIND:
	case STRAIGHT_FLUSH:
	case STRAIGHT:
	case FLUSH:
	case FULL_HOUSE:
		setAllCards(markedCard, true);
		break;
	}
	return true;
}


int PokerHand::highestCardNumber(const int numRes[], int jokers) {
	int highest = CARD_MAX_VALUE; //0;

	if (jokers)
		return CARD_MAX_VALUE;
	while (numRes[highest--] == 0);
	return highest+1;
}

void PokerHand::findCardsWithValue(const PlayerCards& pCards, int value, std::vector<bool>& cards){
	if (value == CARD_MAX_VALUE) value = 1;
	for (unsigned int i=0; i<pCards.getCards().size(); i++){
		Card c = pCards.getCards().at(i);
		if (c.getNumber() == value || c.getSuit() == Card::JOKER){
			cards.at(i) = true;
		}
	}
}


void PokerHand::getScoreOfHand(const PlayerCards& plCards, int firstCardIndex){
	int suitResults[4] = {}, numberResults[15] = {}, jokers = 0;

	cardsToResArrays(plCards, firstCardIndex, suitResults, numberResults, jokers);
	int sameNumbers = countSameNumber(suitResults, numberResults, jokers);
	int sameSuit = countSameSuit( suitResults, numberResults, jokers);
	int longestSeq = countNumberSeq(suitResults, numberResults, jokers);
	if (sameSuit > FLUSH && longestSeq > STRAIGHT)
		score = STRAIGHT_FLUSH + (longestSeq & 0x0f0);
	else
		score = maxOfThree(sameNumbers, sameSuit, longestSeq);
}


int PokerHand::maxOfThree(int int1, int int2, int int3) {
	if (int1 >= int2 && int1 >= int3)
		return int1;
	else if (int2 >= int1 && int2 >= int3)
		return int2;
	else return int3;
}

void PokerHand::setAllCards(std::vector <bool>& markedCards, bool value) {
	for (unsigned int i=0; i< markedCards.size(); i++)
		markedCards.at(i) = value;

}

std::string PokerHand::hexToCardVal(int val){
	char ts[3];
	if (val == 0x0a)
		return "10";
	else if (val == 0x0b)
		return "J";
	else if (val == 0x0c)
		return "Q";
	else if (val == 0x0d)
		return "K";
	else if (val == 0x0e)
		return "A";
	else { // < 10
		sprintf(ts, "%X", val);
		return ts;
	}
}

int PokerHand::convertToScore(int handVal, int firstVal, int secVal){
	return handVal + 0x10 * firstVal + secVal;
}

void PokerHand::breakupScore(int& hand, int& firstVal, int& secVal){
	hand = score & 0xf00;
	firstVal = score/16 & 0x00f;
	secVal = score & 0x00f;
}
