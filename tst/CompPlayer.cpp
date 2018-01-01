/*
 * CompPlayer.cpp
 *
 *  Created on: 2.4.2017
 *      Author: ari
 */

#include "CompPlayer.h"
#include "PokerHand.h"


CompPlayer::CompPlayer(std::string name, int money) : Player(name, money){
}

CompPlayer::~CompPlayer() {
	// TODO Auto-generated destructor stub
}

//Poker function, not used for sökö
void CompPlayer::changeCards(CardDeck& deck) {
	PokerHand ph;
	ph.calcScoreOfHand(playerCards, 0);
	int changed = 0;

	for (unsigned int i = 0; i < ph.getCardsOfHand().size(); i++){
		if (ph.getCardsOfHand().at(i) == false){
			playerCards.changeCard(deck, i);
			changed++;
		}
	}
	std::cout << "Changed " << changed << " cards for player " << getPlayerName() <<"\n";
}

int CompPlayer::bet(int minBet, int maxBet, int round, int bestScore){
	PokerHand phFull, phFour;
	int betMoney, scoreFull, scoreFour;
	scoreFull = phFull.calcScoreOfHand(playerCards, 0);
	scoreFour = phFour.calcScoreOfHand(playerCards, 1);
	bool quit = false;

	// someone has run out of money - bet=0 the rest of this deal
	if (maxBet == 0)
		betMoney = 0;

	// start betting with best visible hand
	else if (minBet == 0 && scoreFour >= bestScore){
		// player has best visible hand at the moment
		if (scoreFull > PAIR)
			betMoney = std::min(10, maxBet);
		else if (scoreFull >= HIGH_CARD + 0x10*11)
			betMoney = std::min(5, maxBet);
		else
			betMoney = 0;
	}

	// not best visible hand, other players bet 0
	else if (minBet == 0 && scoreFour < bestScore){
		if (scoreFull > STRAIGHT_OF_FOUR)
				betMoney = std::min(5, maxBet);
		else
			betMoney = 0;
	}

	// other players betting > 0. Call, raise or quit.
	else if (minBet > 0){
		if (	(scoreFull >= bestScore) ||
				(round <=2 && scoreFull >= HIGH_CARD + 0x10*11) ||
				(round == 3 && scoreFull >= PAIR) ||
				(round >=4 && scoreFull >= STRAIGHT_OF_FOUR)){
			if (evalBetWithMoney(round, minBet))
				betMoney = minBet;
			else // cards ok, but bet too high, quit
				quit = true;
		}
		else // not good enough cards to pay
			quit = true;

	}

	if (quit){
		setGameStatus(false);
		betMoney = 0;
	}
	else
		reduceMoney(betMoney);

	return betMoney;
}

void CompPlayer::dispCards(bool hideFirst) const {
	playerCards.dispCards3(true);
}

void CompPlayer::printBetResult(int bet) const{
	if (gameStatus == false)
		std::cout << getPlayerName() << " quits\n";
	else
		std::cout << getPlayerName() <<" is betting " << bet << std::endl;
}

bool CompPlayer::evalBetWithMoney(int round, int minBet){
	int maxPossibleBet;
	int minPossibleBet = std::min(5, getMoney());

	if (round <=2)
		maxPossibleBet = std::max(minPossibleBet, getMoney()/5);
	else if (round == 3)
		maxPossibleBet = std::max(minPossibleBet, getMoney()/4);
	else if (round == 4)
		maxPossibleBet = std::max(minPossibleBet, getMoney()/3);
	else if (round == 5)
		maxPossibleBet = std::max(minPossibleBet, getMoney()/2);

	if (minBet <= maxPossibleBet)
		return true;
	else
		return false;
}
