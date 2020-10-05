/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: ItemDrop.h
*     Description: This is the base abstract class for all items.
*     An ItemDrop cannot be created directly, instead a new class
*     must be defined and inherit from the ItemDrop to be used.
*     The developer is required to define the use method. 
*     ItemDrop inherits from the cocos2d::Sprite class to give Item objects
*     a "physical" form on screen.
*
*/


#ifndef __ITEM_DROP_H__
#define __ITEM_DROP_H__


#include "cocos2d.h"
#include "Definitions.h"
#include<vector>
#include<string>


using namespace std;

//ItemDrop class
class ItemDrop : public cocos2d::Sprite{
private:
	int Count;
	double DropRate;


public:
	ItemDrop(string NameOfItem, int NumberOfItem, const string& ImageFile, double DropChance);
	int getCount();
	double getDropRate();

	void AnimateItem(cocos2d::Vec2 location);

	//items to make
	static ItemDrop* createGems(int amount, double chance);
	static ItemDrop* createHammers(int amount, double chance);
	static ItemDrop* createLife(int amount, double chance);
	static ItemDrop* createCoins(int amount, double chance);
	static ItemDrop* createBrushes(int amount, double chance);


};

#endif //__ITEM_DROP_H__