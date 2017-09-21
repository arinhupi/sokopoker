/*
 * Player.cpp
 *
 *  Created on: 17.3.2017
 *      Author: ari
 */

#include "Player.h"
#include "PokerHand.h"
#include <iostream>



Player::Player(std::string name, int money): playerName(name), money(money), gameStatus(true) {

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::dispMoney() {
	std::cout << "Name: " << playerName << "\nAmount of money: " << money << " euro" << std::endl;
}


void Player::addToDeck(Card card) {
	playerCards.addToDeck(card);
}


void Player::changeCards(CardDeck& deck) {
	std::cout << "Player::changeCards, virtual not implemented\n";
}


int Player::bet(int minBet, int maxBet, int round, int maxScore){
	std::cout << "Player::bet, virtual not implemented\n";
	return 0;
}

void Player::resetCards() {
	playerCards.resetCards();
}


void Player::dispCards(bool dispFirst) {
	std::cout << "Player::dispCards, virtual not implemented\n";

}

void Player::addMoney(int addedMoney){
	money += addedMoney;
}

void Player::reduceMoney(int reducedMoney){
	if (reducedMoney <= money)
		money -= reducedMoney;
	else{
		money = 0;
		setGameStatus(false);
		std::cout << playerName << " run out of money\n";
	}
}

