/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Hammers.h
*     Description:
*
*
*
*/


#ifndef __HAMMERS_H__
#define __HAMMERS_H__

#include"ItemDrop.h"

class Hammers : public ItemDrop {
public:
	bool use(Player player);
	Hammers(int NumberOfHammers,double DropRate);
};

#endif //__HAMMERS_H__