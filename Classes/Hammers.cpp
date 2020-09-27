/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Hammers.cpp
*     Description:
*
*
*
*/


#include "Definitions.h"
#include "Hammers.h"

bool Hammers::use(Player player) {
	player.addHammers(this->getCount());
	return true;
}

Hammers::Hammers(int NumberOfHammers,double DropRate)
	:ItemDrop("Hammers", NumberOfHammers, IMG_HAMMER,DropRate) {

}