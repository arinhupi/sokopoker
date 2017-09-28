/*
 * SokoGame.h
 *
 *  Created on: 11.9.2017
 *      Author: ari
 */

#ifndef SOKOGAME_H_
#define SOKOGAME_H_


#include "CardDeck.h"
#include "Player.h"
#include "PokerHand.h"

typedef struct {int player; int score;} PokRes;

class SokoGame {
        int roundNr;
public:
        static const int INCLUDE_ALL_CARDS = 0;
        static const int EXCLUDE_FIRST_CARD = 1;
    	SokoGame();
    	virtual ~SokoGame();
        void play();
        void testHands();
        void autoPlay(int);
private:
       	void initPlayers(std::vector<Player*>& players);
        void deal(std::vector<Player*>& players, CardDeck& deck, int count, int round);
        void resetPlayerCards(std::vector<Player*>& pl);
        PokRes findBestHand(const std::vector<Player*>&, int startIndex);
        void showResultsOfRound(std::vector<Player*>&, int potti, int round);
        void dispAllCards(const std::vector<Player*>&, int round);
        void dispHands(const std::vector<Player*>& pl);
        int takeBets(std::vector<Player*>&, int round, int pot);
        int forceBet(std::vector<Player*>&, int bet);
        void resetPlayerStatusAndCards(std::vector<Player*>& pl);
        int activePlayers(const std::vector<Player*>& pl);
        bool checkBets(const std::vector<Player*>& pl, const std::vector<int>& bets);
        int getMinBet(const std::vector<Player*>& pl, unsigned int plIndex, const std::vector<int>& bets);
        int getMaxBet(const std::vector<Player*>& pl, const std::vector<int>& bets);
        int highestScoreId(std::vector<PokerHand>&);
};

#endif /* SOKOGAME_H_ */
