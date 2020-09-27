/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: ItemDrop.h
*     Description:
*
*
*
*/


#ifndef __ITEM_DROP_H__
#define __ITEM_DROP_H__


#include "cocos2d.h"
#include<string>
#include"Player.h"

using namespace std;

//ItemDrop class
class ItemDrop : public cocos2d::Sprite{
private:
	string Name;
	int Count;
	double DropRate;


public:
	ItemDrop(string NameOfItem, int NumberOfItem, const string& ImageFile, double DropChance);
	string getName();
	int getCount();
	double getDropRate();
	
	virtual bool use(Player player) =0;

	void AnimateItem(cocos2d::Vec2 location);
	void FadeOut(float duration);

};

#endif //__ITEM_DROP_H__