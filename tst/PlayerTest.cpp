#include "catch.hpp"
#include "Player.h"

TEST_CASE("Player init+getters", "[Player]"){
	Player player("tester", 10);
	REQUIRE(player.getPlayerName() == "tester");
	REQUIRE(player.getMoney() == 10);
	REQUIRE(player.getGameStatus() == true);
	REQUIRE(player.getPlayerCards().getCardAmount() == 0);

	std::vector<Card> testCards = {{Card::HEART,3}, {Card::SPADE,3}, {Card::HEART,4}, {Card::HEART,5}, {Card::SPADE,6}};
	PlayerCards pCards;
	pCards.setCards(testCards);
	player.setPlayerCards(pCards);
	REQUIRE(player.getPlayerCards().getCardAmount() == 5);

}

TEST_CASE("Player add and reset players deck", "[Player]"){
	Player player("Tester", 20);
	player.addToDeck({Card::HEART, 4});
	player.addToDeck({Card::HEART, 7});
	REQUIRE(player.getPlayerCards().getCardAmount() == 2);
	player.resetCards();
	REQUIRE(player.getPlayerCards().getCardAmount() == 0);
}


TEST_CASE("Player add reduce money", "[Player]"){
	Player player("Tester", 20);
	player.addMoney(5);
	REQUIRE(player.getMoney() == 25);
	player.reduceMoney(10);
	REQUIRE(player.getMoney() == 15);
}

/*


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
	virtual void dispCards(bool firstHidden) const;

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

};
*/
