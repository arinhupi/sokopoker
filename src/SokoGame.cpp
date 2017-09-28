/*
 * SokoGame.cpp
 *
 *  Created on: 11.9.2017
 *      Author: ari
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include "Card.h"
#include "CardDeck.h"
#include "PokerHand.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "CompPlayer.h"
#include "SokoGame.h"

SokoGame::SokoGame() {
	// TODO Auto-generated constructor stub

}

SokoGame::~SokoGame() {
	// TODO Auto-generated destructor stub
}

bool compareByScore(const PokRes& a, const PokRes& b) {
	return a.score < b.score;
}

void SokoGame::deal(std::vector<Player*>& pl, CardDeck& deck, int count, int round) {
	if (round == 2)
		std::cout << "\nDealing first two cards\n";
	else if (round >2)
		std::cout << "\nDealing next card\n";

	for (int i = 0; i < count; i++) {
		for (unsigned int j = 0; j < pl.size(); j++) {
			if (pl.at(j)->getGameStatus() == true) {
				Card card = deck.getFirstCard();
				pl.at(j)->addToDeck(card);
			}
		}
	}
}

void SokoGame::resetPlayerStatusAndCards(std::vector<Player*>& pl) {
	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getMoney() > 0) {
			pl.at(i)->setGameStatus(true);
			pl.at(i)->resetCards();
		}
		else
			pl.at(i)->setGameStatus(false);
	}
}

int SokoGame::takeBets(std::vector<Player*>& pl, int round, int pot) {
	if (round == 1) {
		int betSum = forceBet(pl, 5);
		return betSum; // start betting after second card
	}

	int minBet = 0, maxBet, curBet, potti = 0;
	std::vector<int> bets;
	bets.assign(pl.size(), 0);
	PokRes pr = findBestHand(pl, EXCLUDE_FIRST_CARD);
	std::cout << "Pot now: " << pot << " euros\n";
	std::cout << "Player with best hand starts betting: "
			<< pl.at(pr.player)->getPlayerName() << "\n";
	unsigned int i = pr.player;

	do {
		unsigned int playerId = i % pl.size();
		if (pl.at(playerId)->getGameStatus() == true) {
			minBet = getMinBet(pl, playerId, bets);
			maxBet = getMaxBet(pl, bets);
			curBet = pl.at(playerId)->bet(minBet, maxBet, round, pr.score);
			bets.at(playerId) += curBet;
			potti += curBet;
		}
		i++;
	} while (i < (pr.player + pl.size()) || checkBets(pl, bets) == false);

	return potti;
}

int SokoGame::activePlayers(const std::vector<Player*>& pl) {
	int act = 0;
	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true)
			act++;
	}
	return act;
}

bool SokoGame::checkBets(const std::vector<Player*>& pl, const std::vector<int>& bets) {
	int curBet, prevBet = -1;
	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true) {
			curBet = bets.at(i);
			if (prevBet == -1) // first
				prevBet = curBet;
			else if (curBet != prevBet)
				return false;
		}
	}
	return true;
}

int SokoGame::forceBet(std::vector<Player*>& pl, int bet) {
	int potti = 0;
	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true && pl.at(i)->getMoney() >= bet) {
			pl.at(i)->reduceMoney(bet);
			potti += bet;
		}
	}
	return potti;
}

int SokoGame::getMinBet(const std::vector<Player*>& pl, unsigned int plIndex, const std::vector<int>& bets) {
	int playerBet = bets.at(plIndex), highestBet = 0;
	if (pl.at(plIndex)->getGameStatus() == false)
		return 0;

	for (unsigned int i = 0; i < pl.size(); i++) {
		if (i == plIndex)
			continue;
		if (pl.at(i)->getGameStatus() == true) {
			if (bets.at(i) > highestBet)
				highestBet = bets.at(i);
		}
	}
	return highestBet - playerBet;
}

// find player with least amount of money
int SokoGame::getMaxBet(const std::vector<Player*>&pl, const std::vector<int>& bets) {
	int maxBet = std::numeric_limits<int>::max();
	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true){
			int money = pl.at(i)->getMoney() + bets.at(i);
			if (money < maxBet)
				maxBet = money;
		}
	}
	return maxBet;
}

void SokoGame::dispAllCards(const std::vector<Player*>& pl, int round) {
	if (round == 1)
		return;

	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true) {
			std::cout << "Player " << pl.at(i)->getPlayerName() << " ("
					<< pl.at(i)->getMoney() << " euros left)\n";
			pl.at(i)->dispCards(false);
		}
	}
	std::cout << "\n";
}

PokRes SokoGame::findBestHand(const std::vector<Player*>& pl, int startIndex) {
	std::vector<PokerHand> phandVec(pl.size());
	PokerHand pHand;
	PlayerCards pCards;
	PokRes pr;

	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true) {
			pCards = pl.at(i)->getPlayerCards();
			pHand.getScoreOfHand(pCards, startIndex);
			phandVec.at(i) = pHand;
		} else
			phandVec.at(i).setScore(0);
	}

	// return id of player with highest score
	int bestPlayerId = highestScoreId(phandVec);
	pr.player = bestPlayerId;
	pr.score = phandVec.at(bestPlayerId).getScore();
	return pr;
}

void SokoGame::dispHands(const std::vector<Player*>& pl) {
	PokerHand pHand;
	PlayerCards pCards;

	for (unsigned int i = 0; i < pl.size(); i++) {
		if (pl.at(i)->getGameStatus() == true) {
			pCards = pl.at(i)->getPlayerCards();
			pHand.getScoreOfHand(pl.at(i)->getPlayerCards(), 0);
			std::cout << pl.at(i)->getPlayerName() << ":\t";
			pHand.printHand();
		}
	}
}

void SokoGame::initPlayers(std::vector<Player*>& players) {
	HumanPlayer* player1 = new HumanPlayer("*You*", 100);
	CompPlayer* player2 = new CompPlayer("Jussi", 100);
	CompPlayer* player3 = new CompPlayer("Matti", 100);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
}

void SokoGame::showResultsOfRound(std::vector<Player*>& players, int potti, int round) {
	std::cout << "\n---- Results ----\n";
	if (round == 5)
		dispHands(players);
	PokRes pr = findBestHand(players, INCLUDE_ALL_CARDS);
	players.at(pr.player)->addMoney(potti);
	std::cout << "The winner is " << players.at(pr.player)->getPlayerName() << "\n\n";
}

void SokoGame::play() {
	std::string qstring;
	CardDeck deck(CardDeck::CARDDECK_WITHOUT_JOKERS);
	std::vector<Player*> players;

	initPlayers(players);

	do {
		int pot = 0, cardNr;
		deck.shuffle();
		resetPlayerStatusAndCards(players);
		if (players.at(0)->getGameStatus() == false || activePlayers(players) == 1)
			break;
		for (cardNr = 1; cardNr <= 5; cardNr++) {
			deal(players, deck, 1, cardNr);
			dispAllCards(players, cardNr);
			pot += takeBets(players, cardNr, pot);
			if (activePlayers(players) == 1)
				break;
		}
		showResultsOfRound(players, pot, --cardNr);

		std::cout << "Again (y/n)?\n";
		std::cin >> qstring;
	} while (qstring != "n");

	for (unsigned int i = 0; i < players.size(); i++)
		delete players.at(i);
}

// for testing purposes
void SokoGame::testHands() {
	PokerHand ph;
	std::vector<Card> testCards;
	PlayerCards pCards;

	// flush of four
	testCards = { {Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,7}, {Card::HEART,9}};
	pCards.setCards(testCards);
	pCards.dispCards();
	ph.getScoreOfHand(pCards, 0);
	//ph = pCards.getScoreOfHand();
	ph.printScore();

	// straight of four
	testCards = { {Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}};
	pCards.setCards(testCards);
	pCards.dispCards();
	ph.getScoreOfHand(pCards, 0);
	//ph = pCards.getScoreOfHand();
	ph.printScore();

	// flush
	testCards = { {Card::HEART,3}, {Card::HEART,3}, {Card::HEART,10}, {Card::HEART,7}, {Card::HEART,9}};
	pCards.setCards(testCards);
	pCards.dispCards();
	ph.getScoreOfHand(pCards, 0);
	//ph = pCards.getScoreOfHand();
	ph.printScore();

	// värisuora
	testCards = { {Card::HEART,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::HEART,6}, {Card::HEART,7}};
	pCards.setCards(testCards);
	pCards.dispCards();
	ph.getScoreOfHand(pCards, 0);
	//ph = pCards.getScoreOfHand();
	ph.printScore();

	// värisuora
	testCards = { {Card::HEART,3}, {Card::CLUB,3}, {Card::DIAMOND,3}, {Card::SPADE,3}, {Card::HEART,7}};
	pCards.setCards(testCards);
	pCards.dispCards();
	ph.getScoreOfHand(pCards, 0);
	//ph = pCards.getScoreOfHand();
	ph.printScore();

}

int SokoGame::highestScoreId(std::vector<PokerHand>& ph) {
	int curBest = 0, playerIndex;
	for (unsigned int i = 0; i < ph.size(); i++) {
		int score = ph.at(i).getScore();
		if (score > curBest) {
			curBest = score;
			playerIndex = i;
		}
	}
	return playerIndex;
}

