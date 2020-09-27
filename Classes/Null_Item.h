/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Null_Item.h
*     Description:
*
*
*
*/


#ifndef __NULL_ITEM_H__
#define __NULL_ITEM_H__
#include"ItemDrop.h"

class Null_Item : public ItemDrop {
public:
	bool use(Player player);
	Null_Item();
};

#endif //__NULL_ITEM_H__