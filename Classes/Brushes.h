/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Brushes.h
*     Description:
*
*
*
*/

#ifndef __BRUSHES_H__
#define __BRUSHES_H__
#include"ItemDrop.h"

class Brushes : public ItemDrop {
public:
	bool use(Player player);
	Brushes(int NumberOfBrushes,double DropRate);
};

#endif //__BRUSHES_H__