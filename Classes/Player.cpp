/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Player.cpp
*     Description:
*
*
*
*/


#include"Player.h"

Player::Player(std::string str) {
	this->Name = str;
}

std::string Player::getName() {
	return this->Name;
}

int Player::getBrushes() {
	return this->numBrushes;
}

int Player::getGems() {
	return this->numGems;
}

int Player::getCoins() {
	return this->numCoins;
}

int Player::getHammers() {
	return this->numHammers;
}

int Player::getLife() {
	return this->numLife;
}

bool Player::addBrushes(int n) {
	this->numBrushes += n;
}

bool Player::addHammers(int n) {
	this->numHammers += n;
}

bool Player::addCoins(int n) {
	this->numCoins += n;
}

bool Player::addGems(int n) {
	this->numGems += n;
}

bool Player::addLife(int n) {
	this->numLife += n;
}