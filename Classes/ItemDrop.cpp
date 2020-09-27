/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: ItemDrop.cpp
*     Description:
*
*
*
*/

#include"ItemDrop.h"



ItemDrop::ItemDrop(std::string NameOfItem, int NumberOfItem, const string& ImageFile, double DropChance) {
	this->Name = NameOfItem;
	this->Count = NumberOfItem;
	this->DropRate = DropChance;
	this->initWithFile(ImageFile);
	this->setCascadeOpacityEnabled(true);

	string text = "x";
	text += std::to_string(NumberOfItem);

	cocos2d::Label* label = cocos2d::Label::createWithTTF(text, "fonts/Marker Felt.ttf", 16);
	this->addChild(label);

	label->setPositionX( label->getPositionX() + 20 );
	label->enableOutline(cocos2d::Color4B::ORANGE, 1);

}
	
std::string ItemDrop::getName() {
	return this->Name;
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

void ItemDrop::FadeOut(float duration) {
	this->runAction( cocos2d::FadeOut::create(duration) );
}
