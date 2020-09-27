/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Coins.h
*     Description:
*
*
*
*/


#ifndef __COINS_H__
#define __COINS_H__
#include"ItemDrop.h"

class Coins : public ItemDrop {
public:
	bool use(Player player);
	Coins(int NumberOfCoins,double DropRate);
};

#endif //__COINS_H__