/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: WheelMaker.h
*     Description: This is a "helper" or "construction" class/object for
*     the creation of wheel and items. 
*
*
*
*/


#ifndef __WHEEL_MAKER_H__
#define __WHEEL_MAKER_H__

#include "cocos2d.h"
#include "Wheel.h"
#include "Life.h"
#include "Brushes.h"
#include "Gems.h"
#include "Hammers.h"
#include "Coins.h"



//wheel Builder
class WheelMaker
{
private:
    static vector<ItemDrop*> createItems();
    static float sectorRotation(float sector, Wheel* theWheel);
    static void addItemsToWheel(Wheel* theWheel);

public:
    //static Wheel* createWheel(int sectors, int itemRadius, std::string ImageFileName);

    static Wheel *createWheel(int itemRadius, string ImageFileName, string ImageArrow,
                string ImageFrame);
};

#endif //  __WHEEL_MAKER_H__
