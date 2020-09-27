/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: Wheel.h
*     Description:
*
*
*
*/

#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "cocos2d.h"
#include "Null_Item.h"
#include "Definitions.h"
#include <vector>

//wheel class
class Wheel: public cocos2d::Sprite
{

private:
    int NumberOfSectors;
    int ItemRadius;
    vector<ItemDrop*> ItemDropList;
    int currentSector;
    Sprite* Arrow;
    Sprite* Frame;
    Sprite* theWheel;

public:

    Wheel();
    Wheel(std::string WheelImage, std::string Wheel_arrow, std::string Wheel_frame, vector<ItemDrop*> itemList, int item_radius);

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
