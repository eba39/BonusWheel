/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: UnitTests.cpp
*     Description:
*
*
*
*/

#include "UnitTests.h"

#define CALL_FUNC CC_CALLBACK_0(UnitTests::underConstruction,0.1)

USING_NS_CC;



/*this function will create a menu item for each test that is defined
	each test is added to the menu by creating a MenuItemLabel with a 
	callback to each test
*/
cocos2d::Menu *UnitTests::createMenu(Wheel *theWheel) {

    Menu* UnitTestMenu = Menu::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    vector<MenuItemLabel*> buttonList;

    auto txtObj = ( Label::createWithTTF("Test out of bounds sector: -1337", DEF_FONT, 16) );
    buttonList.push_back( MenuItemLabel::create(txtObj, CC_CALLBACK_0(UnitTests::testOutOfBounds, theWheel )) );
    txtObj = ( Label::createWithTTF("Test 1000 spins", DEF_FONT, 16) );
    buttonList.push_back( MenuItemLabel::create(txtObj, CC_CALLBACK_0(UnitTests::test1000Spins, theWheel )) );
    txtObj = ( Label::createWithTTF("Test item creation", DEF_FONT, 16) );
    buttonList.push_back( MenuItemLabel::create(txtObj, CC_CALLBACK_0(UnitTests::testItemCreation, theWheel )) );
    txtObj = ( Label::createWithTTF("Test no items", DEF_FONT, 16) );
    buttonList.push_back( MenuItemLabel::create(txtObj, CC_CALLBACK_0(UnitTests::testNoItems, theWheel )) );


	//Menu items for each sector that exists on the wheel are created dynamically.
    for(int i = 0; i < theWheel->getNumberOfSectors(); i++){
        std::string sectorText = "Test sector ";
        sectorText += to_string(i) + ":" + theWheel->getItem(i)->getName() + "X" + to_string(theWheel->getItem(i)->getCount());
        txtObj = ( Label::createWithTTF(sectorText, DEF_FONT, 16) );
        buttonList.push_back( MenuItemLabel::create(txtObj, CC_CALLBACK_0(UnitTests::testSectorInput, theWheel, i )) );
    }
	
	//positioning and color added to improve visibility of menu
    DrawNode* box;
    int spacing = 23;
    int count = 0;
    for(auto txt: buttonList){
        box = DrawNode::create();
        Rect aabb = txt->getBoundingBox();
        box->drawSolidRect(aabb.origin,  aabb.origin+aabb.size, Color4F(1,0,0,0.6) );
        txt->addChild(box, -1);
        box->setPositionX( aabb.getMaxX());
        box->setPositionY( aabb.getMaxY() );
        UnitTestMenu->addChild(txt);
        txt->setPosition(Vec2::ZERO);
        txt->setPositionY(-count*spacing);

        count++;

    }

    UnitTestMenu->setName(DEBUG_TAG);
    return UnitTestMenu;
}



bool UnitTests::init() {


    return true;
}

void UnitTests::testOutOfBounds(Wheel* theWheel) {
    LOGGER("testing index -1337...");
    theWheel->getItem(-1337);
    theWheel->setCurrentSector(-1337);
    theWheel->AnimateWheel();
}

void UnitTests::testSectorInput(Wheel* theWheel, int Sector) {
    LOGGER("Testing sector: %d", Sector );
    theWheel->setCurrentSector( Sector );
    ItemDrop* item = theWheel->AnimateWheel();
}

void UnitTests::test1000Spins(Wheel* theWheel) {
    //code for getting random number
    vector<float> sectorHitCounts = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    for(int i = 0; i < 1000; i++){
        theWheel->spin(false);
        int sector = theWheel->getCurrentSector();
        sectorHitCounts[sector]++;
    }

    vector<string> output_to_screen;
    output_to_screen.push_back(":::1000TESTS COMPLETE:::");
    LOGGER(":::1000TESTS COMPLETE:::");
    int index = 0;
    for(int hits: sectorHitCounts){
        float avg = hits/1000.0;
        LOGGER("item: %sX%d\t\thits: %d\t\tavg: %f", theWheel->getItem(index)->getName().c_str(),theWheel->getItem(index)->getCount(), hits, avg);
        output_to_screen.push_back( "item: " + theWheel->getItem(index)->getName() + "X" + to_string( theWheel->getItem(index)->getCount() ) + "    hits: " + to_string(hits) + "    avg: " + to_string(avg) );
        index++;
    }

    UnitTests::showLog(output_to_screen, dynamic_cast<Scene *>(theWheel->getParent()));

}


void UnitTests::testItemCreation(Wheel* theWheel) {

    vector<ItemDrop*> itemList = theWheel->getItemDropList();
    vector<string> output_to_screen;
    output_to_screen.push_back(":::ITEM CREATION:::");

    int index = 0;

    for(ItemDrop* item: itemList){
        theWheel->getWheelSprite()->addChild(item);
        output_to_screen.push_back("item[" + to_string(index) + "]" + " -> Name: " + item->getName() + "::: Count = " + to_string(item->getCount()) );
        LOGGER( "item[%d] -> Name: %s  ::: Count = %d", index++,item->getName().c_str(), item->getCount()   );
    }

    showLog(output_to_screen, dynamic_cast<Scene *>(theWheel->getParent()));

}

void UnitTests::testNoItems(Wheel* theWheel) {
    LOGGER("Removing all items from wheel list!");
    vector<ItemDrop*> itemList = theWheel->getItemDropList();
    itemList.erase(itemList.begin(), itemList.end());
    theWheel->getWheelSprite()->removeAllChildren();
}


void UnitTests::showLog(vector<string> output_to_screen, Scene* screen) {
    Menu* tempMenu = Menu::create();
    tempMenu->setName("temp menu");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);


    DrawNode* box;
    int spacing = 23;
    int count = 0;
    output_to_screen.push_back("---PRESS ON TEXT TO CLOSE IT---");
    for(string output: output_to_screen){
        auto txtObj = Label::createWithTTF(output, DEF_FONT, 16);
        auto buttonObj = MenuItemLabel::create(txtObj, CC_CALLBACK_0(killLog, screen));
        //entries.push_back(buttonObj);

        box = DrawNode::create();
        Rect aabb = buttonObj->getBoundingBox();
        box->drawSolidRect(aabb.origin,  aabb.origin+aabb.size, Color4F(0,0,1,0.6) );
        buttonObj->addChild(box, -1);
        box->setPositionX( aabb.getMaxX());
        box->setPositionY( aabb.getMaxY() );
        tempMenu->addChild(buttonObj);
        buttonObj->setPosition(Vec2::ZERO);
        buttonObj->setPositionY(-count*spacing);
        count++;
    }
    tempMenu->setScale(0.5);

    screen->addChild(tempMenu);
    tempMenu->setPositionX( tempMenu->getPositionX()-centerScreen.x/2);

}

void UnitTests::killLog(Scene *screen) {
    screen->removeChildByName("temp menu");
}




