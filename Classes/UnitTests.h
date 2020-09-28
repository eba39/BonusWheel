/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: UnitTests.h
*     Description: The UnitTests class holds all of functions
*     for the user to test the app during run time.
*     Output is shown in the console.
*
*/

#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

#include "cocos2d.h"
#include "WheelMaker.h"

#define LOG_TAG2 "helloworld"
#define LOGGER(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG2,__VA_ARGS__)

//wheel class
class UnitTests: public cocos2d::Menu
{

public:
    static cocos2d::Menu* createMenu(Wheel* theWheel);
    //static Wheel* theWheel;
    virtual bool init();
    CREATE_FUNC(UnitTests);



    //tests a sector bigger than the amount of wheel sectors
    static void testOutOfBounds(Wheel* theWheel);

    //tests any sector that the user inputs
    static void testSectorInput(Wheel* theWheel, int Sector);

    //tests the wheel 1000x/displays prize chance
    static void test1000Spins(Wheel* theWheel);

    //tests the creation of items and will see if it is to spec.
    static void testItemCreation(Wheel* theWheel);

    //tests game with no items
    static void testNoItems(Wheel* theWheel);

    //test ItemDrop creation with NULL inputs
    static void createInvalidItem();

	//this function was used as a placeholder for menu creation
    static void underConstruction(float dt);


};

#endif //  __UNIT_TESTS_H__
