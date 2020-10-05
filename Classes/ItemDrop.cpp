/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: ItemDrop.cpp
*     Description:
*
*
*
*/

#include"ItemDrop.h"
#include "Definitions.h"



ItemDrop::ItemDrop(std::string NameOfItem, int NumberOfItem, const string& ImageFile, double DropChance) {
	//this->Name = NameOfItem;

	//this will ensure that the Sprite::init function gets called.
	if( this->initWithFile(ImageFile) ) {

		this->setName(NameOfItem);
		this->Count = NumberOfItem;
		this->DropRate = DropChance;
		this->setCascadeOpacityEnabled(true);

		string text = "x";
		text += std::to_string(NumberOfItem);

		cocos2d::Label *label = cocos2d::Label::createWithTTF(text, "fonts/Marker Felt.ttf", 16);
		this->addChild(label);

		label->setPositionX(label->getPositionX() + 20);
		label->enableOutline(cocos2d::Color4B::ORANGE, 1);
	}

}


int ItemDrop::getCount() {
	return this->Count;
}

double ItemDrop::getDropRate(){
	return this->DropRate;
}

void ItemDrop::AnimateItem(cocos2d::Vec2 location) {

	auto enlarge = cocos2d::ScaleTo::create(0.2, 2.0);
	auto moveDown = cocos2d::MoveTo::create(0.75, location);
	auto action = cocos2d::Spawn::createWithTwoActions(enlarge,moveDown);

	this->runAction(action);

}


ItemDrop *ItemDrop::createGems(int amount, double chance) {
	return new ItemDrop("Gems", amount, IMG_GEM, chance);
}

ItemDrop *ItemDrop::createHammers(int amount, double chance) {
	return new ItemDrop("Hammers", amount, IMG_HAMMER, chance);
}

ItemDrop *ItemDrop::createLife(int amount, double chance) {
	return new ItemDrop("Life", amount, IMG_HEART, chance);
}

ItemDrop *ItemDrop::createCoins(int amount, double chance) {
	return new ItemDrop("Coins", amount, IMG_COIN, chance);
}

ItemDrop *ItemDrop::createBrushes(int amount, double chance) {
	return new ItemDrop("Brushes", amount, IMG_BRUSH, chance);
}


