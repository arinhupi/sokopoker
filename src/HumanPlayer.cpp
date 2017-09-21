/*
 * HumanPlayer.cpp
 *
 *  Created on: 19.3.2017
 *      Author: ari
 */

#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(std::string name, int money) : Player(name, money) {

}

HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

// poker function, not applicable to soko
void HumanPlayer::changeCards(CardDeck& deck) {
	//std::cout << "HumanPlayer::changeCards\n";
	playerCards.dispCards2();
	std::string cardString;
	std::cout << "give number of cards you want to change, 1-change 0-keep, e.g. 10100\n";
	do{
		std::cin >> cardString;
	}while (cardString.length() != 5);

	for (int i=0; i<5; i++){
		if (cardString.at(i) == '1')
			playerCards.changeCard(deck, i);
	}
}


int HumanPlayer::bet(int minBet, int maxBet, int round, int bestScore){
	std::string betString;
	int bet;
	do{
	std::cout << "give your bet: b" << minBet << " - " << maxBet <<", q to quit\n";
		std::cin >> betString;
	} while( !betIsLegal(betString, minBet, maxBet, bet));

	return bet;
}

bool HumanPlayer::betIsLegal(const std::string& betString, int minBet, int maxBet, int& bet){

	if (betString.at(0) == 'q'){
		setGameStatus(false);
		std::cout << "You quit\n";
		bet = 0;
		return true;
	}
	else if (betString.at(0) == 'b'){
		std::string betStringSub = betString.substr(1, betString.length());
		int userBet = atoi(betStringSub.c_str());
		if (userBet <= maxBet && userBet >= minBet){
			bet = userBet;
			std::cout<<"Your bet is " << userBet << std::endl;
			reduceMoney(userBet);
			return true;
		}
	}

	return false;
}

void HumanPlayer::dispCards(bool firstHidden){
	playerCards.dispCards3(firstHidden);
}
