/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Null_Item.h
*     Description: The Null_Item class exists to support 
*     the Null Object pattern to avoid unnexpected null 
*     values that could potentially cause issues.
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