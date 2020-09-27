/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Gems.h
*     Description:
*
*
*
*/


#ifndef __GEMS_H__
#define __GEMS_H__


#include"ItemDrop.h"

class Gems : public ItemDrop {
public:
	bool use(Player player);
	Gems(int NumberOfGems,double DropRate);
};

#endif //__GEMS_H__