/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Gems.cpp
*     Description:
*
*
*
*/


#include "Gems.h"
#include "Definitions.h"

bool Gems::use(Player player) {
	player.addGems( this->getCount() );
	return true;
}

Gems::Gems(int NumberOfGems,double DropRate)
	:ItemDrop("Gems", NumberOfGems, IMG_GEM,DropRate) {
	
}