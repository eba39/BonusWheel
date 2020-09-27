/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Wheel.cpp
*     Description:
*
*
*
*/


#include "Wheel.h"

USING_NS_CC;

#define LOG_TAG2 "helloworld"
#define LOGGER(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG2,__VA_ARGS__)

Wheel::Wheel(std::string WheelImage, std::string Wheel_arrow, std::string Wheel_frame, vector<ItemDrop*> itemList, int item_radius){

    this->Arrow = Sprite::create(Wheel_arrow);
    //this->Frame = Sprite::create(Wheel_frame);
    this->theWheel = Sprite::create(WheelImage);
    this->initWithFile(Wheel_frame);
    this->addChild(this->Arrow);
    this->addChild(this->theWheel,-1);
    theWheel->setPosition(this->getCenterOfWheel());
    Arrow->setPosition(Vec2(this->getCenterOfWheel().x, this->getCenterOfWheel().y+this->getCenterRect().getMidY()-10));

    this->ItemDropList = itemList;
    this->NumberOfSectors = itemList.size();
    this->ItemRadius = item_radius;
    this->ItemDropList.push_back(new Null_Item());
}


Wheel::Wheel() {
    this->ItemDropList.push_back( new Null_Item() );
    this->currentSector=this->ItemDropList.size()-1;
}

vector<ItemDrop*> Wheel::getItemDropList() {
    return this->ItemDropList;
}

int Wheel::getItemRadius() {
    return this->ItemRadius;
}

int Wheel::getNumberOfSectors() {
    return this->NumberOfSectors;
}

Sprite* Wheel::getWheelSprite(){
    return this->theWheel;
}

void Wheel::setNumberOfSectors(int numOfSectors) {
    this->NumberOfSectors = numOfSectors;
}

void Wheel::setItemDropList(vector<ItemDrop*> itemList) {
    this->ItemDropList = itemList;
}

void Wheel::setItemRadius(int itemRadius) {
    this->ItemRadius = itemRadius;
}

void Wheel::setCurrentSector(int s) {
    if(s < this->getNumberOfSectors() && s >= 0) {
        this->currentSector = s;
    }else{//fallsafe for out of bounds sectors
        this->currentSector = this->ItemDropList.size()-1;
    }
}


ItemDrop* Wheel::AnimateWheel(){

    float sectorSize = 360.0/this->getNumberOfSectors();
    float itemOffset = sectorSize/2;
    float rotation = ( sectorSize * this->getCurrentSector() ) + itemOffset;

    //if sector is closer to the beginning, wheel will do an extra turn
    if( (this->getCurrentSector()/sectorSize) > 0.625 )
        rotation += 360.0;

    //reset wheel position before animating
    this->setRotation(0.0);

    auto startSpin = RotateBy::create(1.0,360);
    auto slowSpin = RotateBy::create(1.75, 360);
    float spinTime = (rotation*2)/150.0;
    auto lastSpin = RotateBy::create(spinTime,rotation);
    auto overshoot = RotateBy::create(0.4, WHEEL_BOUNCE_END);
    auto revBounce = RotateBy::create(0.4, -WHEEL_BOUNCE_END);

    auto fadeWheelOut = CallFunc::create([this]() {

        ItemDrop* prize = this->getItem(this->getCurrentSector());

        auto fadeAction = FadeOut::create(0.5);

        this->runAction(fadeAction);
        this->theWheel->runAction(fadeAction->clone());
        this->Arrow->runAction(fadeAction->clone());

        prize->AnimateItem( this->getCenterOfWheel() );

        int index = 0;
        for(ItemDrop* item: this->getItemDropList()){
            if(index++!=this->getCurrentSector())
                item->runAction( fadeAction->clone() );
        }

    });

    auto spinSequence = Sequence::create(startSpin,slowSpin,lastSpin,overshoot,revBounce, fadeWheelOut, nullptr);

    this->theWheel->runAction( spinSequence );
    return this->ItemDropList[this->getCurrentSector()];

}

cocos2d::Vec2 Wheel::getCenterOfWheel() {
    Vec2 centerWheel = Vec2( this->getCenterRect().getMidX(), this->getCenterRect().getMidY() );
    return centerWheel;
}

int Wheel::getCurrentSector() {
    return this->currentSector;
}

ItemDrop *Wheel::getItem(int Sector) {

    if(Sector >= this->ItemDropList.size()-1 || Sector < 0)
        return this->ItemDropList[this->ItemDropList.size()-1];

    return this->ItemDropList[Sector];
}

ItemDrop *Wheel::spin(bool playAnimation) {
    int sector = -1;

    int total = 0;
    for(ItemDrop* item : this->ItemDropList){
        total += item->getDropRate();
    }

    int rand = cocos2d::RandomHelper::random_int(1, total);
    total = 0;

    for(ItemDrop* item : this->ItemDropList){
        sector++;
        int lower = total;
        total = lower+item->getDropRate();

        if(rand > lower && rand <= total)
            break;
    }

    this->currentSector = sector;

    if(playAnimation)
        return this->AnimateWheel();

    return this->ItemDropList[this->getCurrentSector()];
}






