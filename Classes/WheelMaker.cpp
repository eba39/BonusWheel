/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: WheelMaker.cpp
*     Description:
*
*
*
*/



#include "WheelMaker.h"
#include <string>
#include <cmath>



#define LOG_TAG2 "helloworld"
#define LOGGER(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG2,__VA_ARGS__)

USING_NS_CC;
Wheel* WheelMaker::createWheel(int itemRadius, std::string ImageFileName,std::string ImageArrow, std::string ImageFrame) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    //create wheel and center it
    Wheel* tWheel = new Wheel(ImageFileName, ImageArrow,ImageFrame, createItems(), itemRadius);

    //tWheel->initWithFile(  ImageFileName  );
    tWheel->setPosition(  centerScreen  );
    tWheel->setCurrentSector(0);


    //create itemDrops here;
    //tWheel->setItemDropList(  createItems()  );
    //tWheel->setItemRadius(  itemRadius  );
    //tWheel->setNumberOfSectors(  sectors  );


    //add items to wheel object
    addItemsToWheel(tWheel);

    return tWheel;
}

vector<ItemDrop*> WheelMaker::createItems() {

    vector<ItemDrop*> items;
    items.push_back(new Life(AMT_SEC_1, RATE_LIFE_X30));
    items.push_back(new Brushes(AMT_SEC_2, RATE_BRUSH_X3));
    items.push_back(new Gems(AMT_SEC_3,RATE_GEMS_X35));
    items.push_back(new Hammers(AMT_SEC_4,RATE_HAMMER_X3));
    items.push_back( new Coins(AMT_SEC_5,RATE_COINS_X750));
    items.push_back(new Brushes(AMT_SEC_6, RATE_BRUSH_X1));
    items.push_back(new Gems(AMT_SEC_7, RATE_GEMS_X75));
    items.push_back(new Hammers(AMT_SEC_8, RATE_HAMMER_X1));

    return items;
}

float WheelMaker::sectorRotation(float sector, Wheel* theWheel) {
    float sectorSpace = 360.0/theWheel->getNumberOfSectors();
    float sectorOffset = sectorSpace/2.0;

    return ( sectorSpace*sector ) + sectorOffset + ROTATION_OFFSET;
}

void WheelMaker::addItemsToWheel(Wheel* theWheel) {

    Vec2 centerWheel = theWheel->getCenterOfWheel();
    float rad = theWheel->getItemRadius();
    vector<ItemDrop*> itemList = theWheel->getItemDropList();

    //set item positions around wheel
    for( int sector = 0;  sector < theWheel->getNumberOfSectors();  sector++ ){

        theWheel->getWheelSprite()->addChild(  itemList[ sector ]  );

        float theta = sectorRotation(sector,theWheel);
        itemList[ sector ]->setRotation( -theta + ROTATION_OFFSET );
        itemList[ sector ]->setPosition(Vec2(( rad*std::cos(theta*PI/180) ) + centerWheel.x,
                                             ( rad * std::sin(theta*PI/180 ) )+centerWheel.y));

    }

}


