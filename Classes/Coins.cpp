/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Coins.cpp
*     Description:
*
*
*
*/

#include<iostream>
#include "Coins.h"
#include "Definitions.h"

bool Coins::use(Player player) {
	player.addCoins(this->getCount());
	return true;
}

Coins::Coins(int NumberOfCoins,double DropRate)
	:ItemDrop("Coins", NumberOfCoins, IMG_COIN, DropRate) {

}