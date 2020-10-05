/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Wheel.h
*     Description: This class holds all of the functionality for the
*     the wheel seen on screen. This includes animations and game behaviors.
*     
*
*/

#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "cocos2d.h"
#include "ItemDrop.h"
#include "Definitions.h"
#include <vector>

USING_NS_CC;

//wheel class
class Wheel: public cocos2d::Sprite
{

private:

    int NumberOfSectors;
    int ItemRadius;
    int currentSector;

    vector<ItemDrop*> ItemDropList;

    Sprite* Arrow;
    Sprite* theWheel;

    static double calculateSectorRotation(Wheel* theWheel, int sector);
    static void placeItemsAroundWheel(Wheel* theWheel);

public:

    Wheel(std::string WheelImage, std::string Wheel_arrow, std::string Wheel_frame, vector<ItemDrop*> itemList, int item_radius);
    static Wheel* createWheel(vector<ItemDrop*> ItemList);

    //setters
    void setNumberOfSectors(int numOfSectors);
    void setItemRadius(int itemRadius);
    void setItemDropList(vector<ItemDrop*> itemList);
    void setCurrentSector(int s);


    //getters
    int getNumberOfSectors();
    int getItemRadius();
    int getCurrentSector();
    Sprite* getWheelSprite();
    vector<ItemDrop*> getItemDropList();
    ItemDrop* getItem(int Sector);
    cocos2d::Vec2 getCenterOfWheel();

    //function
    ItemDrop* AnimateWheel();
    ItemDrop* spin(bool playAnimation);

};

#endif //  __WHEEL_H__
