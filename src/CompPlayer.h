/*
 * CompPlayer.h
 *
 *  Created on: 2.4.2017
 *      Author: ari
 */

#ifndef COMPPLAYER_H_
#define COMPPLAYER_H_

#include "Player.h"

class CompPlayer: public Player {
public:
	CompPlayer(std::string, int);
	virtual ~CompPlayer();
	void changeCards(CardDeck&);
	int bet(int minBet, int maxBet, int round, int bestScore);
	void dispCards(bool firstHidden);
};

#endif /* COMPPLAYER_H_ */