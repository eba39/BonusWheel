/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Life.h
*     Description:
*
*
*
*/


#ifndef __LIFE_H__
#define __LIFE_H__


#include"ItemDrop.h"

class Life : public ItemDrop {
public:
	bool use(Player player);
	Life(int NumberOfLives, double DropRate);
};

#endif //__LIFE_H__