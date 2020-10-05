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
    this->theWheel = Sprite::create(WheelImage);
    this->initWithFile(Wheel_frame);
    this->addChild(this->Arrow);
    this->addChild(this->theWheel,-1);
    theWheel->setPosition(this->getCenterOfWheel());
    Arrow->setPosition(Vec2(this->getCenterOfWheel().x, this->getCenterOfWheel().y+this->getCenterRect().getMidY()-10));

    this->ItemDropList = itemList;
    this->NumberOfSectors = itemList.size();
    this->ItemRadius = item_radius;
    this->currentSector = 0;
    this->placeItemsAroundWheel(this);


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
        this->currentSector = 0;
    }
}

//this function handles complete animation for the wheel
ItemDrop* Wheel::AnimateWheel(){

    float sectorSize = 360.0/this->getNumberOfSectors();
    float itemOffset = sectorSize/2;
    float rotation = ( sectorSize * this->getCurrentSector() ) + itemOffset;

    //if sector is closer to the beginning, wheel will do an extra turn
    if( (this->getCurrentSector()/sectorSize) > 0.625 )
        rotation += 360.0;

    //reset wheel position before animating
    this->setRotation(0.0);
	
	/*
	 * Animation are created by using 5 different RotateBy actions to make will spin at varying speeds.
	 * However this makes movement very jerky on screen.
	 *
	 * I would like to know how to better create a spinning animation, I think using Cocos Physics objects would be better
	 * or using the update() function could some how be used to update the speed of the spin.
	*/
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

        /*
         * FadeOut actions are given to each item except for the "prize" item so that it can be shown on screen.
         * This ultimately undermines the purpose of the cascadeOpacityEnabled option to quickly fade out an object with all of it's child objects.
         * I use this loop because I cannot find an good solution that allows me to keep the prize item on screen.
         */
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

	//if sector is out of bounds, the first item will be returned
    if(Sector >= this->ItemDropList.size() || Sector < 0)
        return this->ItemDropList[0];

    return this->ItemDropList[Sector];
}


/*
 * this function is called when player presses play button.
 * A boolean value is passed to decided if animation is played or not
 * when testing 1000 spins, a false value is passed to skip all animations
 */
ItemDrop *Wheel::spin(bool playAnimation) {
    int sector = -1;

	/*
	 * total item drop rates are added to implement dynamic wheel sizes
	 * total is used to get a random value between 1 and total
	 */
    int total = 0;
    for(ItemDrop* item : this->ItemDropList){
        total += item->getDropRate();
    }

    int rand = cocos2d::RandomHelper::random_int(1, total);
    total = 0;
	/*
	 * This loop adds drop rates until a middle value is found.
	 * Which ever item's drop rate breaks the loop, is the item that the player wins
	 * This loop allows for varying numbers of items/sectors per wheel.
	 */
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

Wheel *Wheel::createWheel(vector<ItemDrop*> ItemList) {
    return new Wheel(IMG_WHEEL, IMG_WHEEL_ARROW, IMG_WHEEL_BORDER, ItemList, WHEEL_ITEM_RADIUS);
}

double Wheel::calculateSectorRotation(Wheel *theWheel, int sector) {
    float sectorSpace = 360.0/theWheel->getNumberOfSectors();
    float sectorOffset = sectorSpace/2.0;

    return ( sectorSpace*sector ) + sectorOffset + ROTATION_OFFSET;
}

void Wheel::placeItemsAroundWheel(Wheel *theWheel) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    theWheel->setPosition(  centerScreen  );

    Vec2 centerWheel = theWheel->getCenterOfWheel();
    float rad = theWheel->getItemRadius();
    vector<ItemDrop*> itemList = theWheel->getItemDropList();

    //set item positions around wheel
    for( int sector = 0;  sector < theWheel->getNumberOfSectors();  sector++ ){

        theWheel->getWheelSprite()->addChild(  itemList[ sector ]  );

        float theta = calculateSectorRotation(theWheel, sector);
        itemList[ sector ]->setRotation( -theta + ROTATION_OFFSET );
        itemList[ sector ]->setPosition(Vec2(( rad*std::cos(theta*PI/180) ) + centerWheel.x,
                                             ( rad * std::sin(theta*PI/180 ) )+centerWheel.y));

    }

}





