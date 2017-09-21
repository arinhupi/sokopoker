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
	ph.getScoreOfHand(playerCards, 0);
	int changed = 0;

	for (unsigned int i = 0; i < ph.getCardsOfHand().size(); i++){
		if (ph.getCardsOfHand().at(i) == false){
			playerCards.changeCard(deck, i);
			changed++;
		}
	}
	std::cout << "Changed " << changed << " cards for player " << getPlayerName() <<"\n";
}

// needs major improvement
int CompPlayer::bet(int minBet, int maxBet, int round, int bestScore){
	PokerHand ph;
	int betMoney, score;
	ph.getScoreOfHand(playerCards, 0);
	score = ph.getScore();

	if (maxBet == 0)
		betMoney = 0;
	else if (minBet == 0){
		if (score >= bestScore && score > PAIR)
			betMoney = std::min(10, maxBet);
		else
			betMoney = 5;
	}
	else if (minBet > 0){
		if (ph.getScore() >= bestScore)
			betMoney = minBet;
		else if (round <=3 && ph.getScore() >= HIGH_CARD + 0x10*11)
			betMoney = minBet;
		else if (round >=3 && ph.getScore() >= TWO_PAIRS)
			betMoney = minBet;
		else {
			setGameStatus(false);
			std::cout << getPlayerName() << " quits\n";
			betMoney = 0;
		}
	}
	std::cout << getPlayerName() <<" is betting " << betMoney << std::endl;
	reduceMoney(betMoney);
	return betMoney;
}

void CompPlayer::dispCards(bool hideFirst){
	playerCards.dispCards3(true);
}
