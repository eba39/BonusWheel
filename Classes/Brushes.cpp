/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Brushes.cpp
*     Description:
*
*
*
*/


#include "Definitions.h"
#include "Brushes.h"

bool Brushes::use(Player player) {
	player.addBrushes(this->getCount());
	return true;
}

Brushes::Brushes(int NumberOfBrushes,double DropRate)
	:ItemDrop("Brushes", NumberOfBrushes, IMG_BRUSH,DropRate) {

}