#include "catch.hpp"
#include "CompPlayer.h"
#include "PokerHand.h"

TEST_CASE("CompPlayer bet, player has best hand (pair)", "[CompPlayer]"){
	CompPlayer player("comp", 100);
	PlayerCards myCards;
	myCards.setCards({{Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}});
	player.setPlayerCards(myCards);
	// max bet = 0
	REQUIRE(player.bet(0, 0, 1, HIGH_CARD) == 0);
	// max bet = 20
	REQUIRE(player.bet(0, 20, 1, HIGH_CARD) == 10);
	// min bet = 10 
	REQUIRE(player.bet(10, 20, 1, HIGH_CARD) == 10); 
	// min bet = 20, too high
	REQUIRE(player.bet(20, 20, 1, HIGH_CARD) == 0); 
}


TEST_CASE("CompPlayer bet, player has best hand but worse than pair", "[CompPlayer]"){
	CompPlayer player("comp", 100);
	PlayerCards myCards;

	myCards.setCards({{Card::HEART,12}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,9}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(0, 20, 1, HIGH_CARD) == 5); 

	myCards.setCards({{Card::HEART,10}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,9}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(0, 20, 1, HIGH_CARD) == 0); 
}

TEST_CASE("CompPlayer bet, min bet=0, player doesnt have best hand ", "[CompPlayer]"){
	CompPlayer player("comp", 100);
	PlayerCards myCards;

	// highest card Q -> pay 0
	myCards.setCards({{Card::HEART,12}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,9}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(0, 20, 1, FIVE_OF_A_KIND) == 0); 

	// straight of four -> pay 5
	myCards.setCards({{Card::HEART,12}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(0, 20, 1, FIVE_OF_A_KIND) == 5); 
}

TEST_CASE("CompPlayer bet, min bet > 0, player has best hand ", "[CompPlayer]"){
	CompPlayer player("comp", 100);
	PlayerCards myCards;

	// straight of 4
	myCards.setCards({{Card::HEART,12}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(10, 20, 1, HIGH_CARD) == 10);
	REQUIRE(player.bet(40, 60, 1, HIGH_CARD) == 0);  

}

TEST_CASE("CompPlayer bet, min bet > 0, player doesnt have best hand ", "[CompPlayer]"){
	CompPlayer player("comp", 100);
	PlayerCards myCards;

	// straight of 4
	myCards.setCards({{Card::HEART,12}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}});
	player.setPlayerCards(myCards);
	REQUIRE(player.bet(10, 20, 1, FLUSH) == 10);
	REQUIRE(player.bet(40, 60, 1, FLUSH) == 0);  
}

/*
class CompPlayer: public Player {
public:
	CompPlayer(std::string, int);
	virtual ~CompPlayer();
	void changeCards(CardDeck&);
	int bet(int minBet, int maxBet, int round, int bestScore);
	void printBetResult(int bet) const;
	void dispCards(bool firstHidden) const;

};

*/
