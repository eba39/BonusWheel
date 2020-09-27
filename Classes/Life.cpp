/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Life.cpp
*     Description:
*
*
*
*/

#include "Life.h"
#include "Definitions.h"
bool Life::use(Player player) {
	player.addLife(this->getCount() );
	return true;
}

Life::Life(int NumberOfLives,double DropRate)
	:ItemDrop("Life", NumberOfLives, IMG_HEART,DropRate) {

}