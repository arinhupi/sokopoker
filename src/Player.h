/*
 * Player.h
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#ifndef PLAYER_H_
#define PLAYER_H_


#include <string>
#include <vector>

#include "Card.h"
#include "CardDeck.h"
#include "PlayerCards.h"

class Player {
protected:
	std::string playerName;
	PlayerCards playerCards;
	int money;
	bool gameStatus; // false=quit
public:
	Player(std::string, int);
	virtual ~Player();
	void dispMoney();
	void addToDeck(Card);
	void addMoney(int added);
	void reduceMoney(int reduced);
	virtual void changeCards(CardDeck&);
	virtual int bet(int minBet, int maxBet, int round, int bestScore);
	void resetCards();
	virtual void dispCards(bool firstHidden);

	const PlayerCards& getPlayerCards() const {
		return playerCards;
	}

	const std::string& getPlayerName() const {
		return playerName;
	}

	const bool getGameStatus() const {
		return gameStatus;
	}

	void setPlayerCards(const PlayerCards& playerCards) {
		this->playerCards = playerCards;
	}

	void setMoney(int money) {
			this->money = money;
	}

	void setGameStatus(bool gameStatus) {
			this->gameStatus = gameStatus;
	}

	int getMoney() const {
		return money;
	}

private:
	std::vector<int> &askCardNumbers();
};


#endif /* PLAYER_H_ */
