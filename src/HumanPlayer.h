/*
 * HumanPlayer.h
 *
 *  Created on: 19.3.2017
 *      Author: ari
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer: public Player {
public:
	HumanPlayer(std::string, int);
	virtual ~HumanPlayer();
	void changeCards(CardDeck&);
	int bet(int minBet, int maxBet, int round, int bestScore);
	bool betIsLegal(const std::string& betString, int minBet, int maxBet, int& bet);
	void dispCards(bool firstHidden);

};

#endif /* HUMANPLAYER_H_ */
