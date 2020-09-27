/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: GameScene.cpp
*     Description: 
*
*
*
*/
#include "GameScene.h"
#include "Definitions.h"
#include "UnitTests.h"
#include <string>
#include <cmath>


#define LOG_TAG2 "helloworld"
#define LOGGER(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG2,__VA_ARGS__)

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

MenuItemImage* GameScene::closeButtonInit(){

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MenuItemImage* button = MenuItemImage::create(
            IMG_CLOSE_NORMAL,
            IMG_CLOSE_SEL,
            CC_CALLBACK_1(GameScene::menuCloseCallback, this));


    float x = origin.x + visibleSize.width - button->getContentSize().width/2;
    float y = origin.y + button->getContentSize().height/2;
    button->setPosition(Vec2(x,y));


    return button;
}


cocos2d::MenuItemImage* GameScene::createPlayButton(Wheel* theWheel ,std::string ImageFileName) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);


    MenuItemImage* button = MenuItemImage::create(ImageFileName, ImageFileName, CC_CALLBACK_0(GameScene::playGame, theWheel) );

    Label* txt = Label::createWithTTF("Play On", DEF_FONT, 20);

    button->addChild(txt);
    txt->setPosition(button->getContentSize().width/2, button->getContentSize().height/2 +2);
    txt->enableOutline(cocos2d::Color4B::BLACK, 1);
    button->setPosition(centerScreen);


    return button;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    /////////////////////////////
    auto closeItem = this->closeButtonInit();

    Wheel* w = WheelMaker::createWheel(WHEEL_ITEM_RADIUS, IMG_WHEEL, IMG_WHEEL_ARROW,IMG_WHEEL_BORDER);
    w->setScale(WHEEL_SCALE-0.2);
    this->addChild(w);

    auto wheelButton = createPlayButton(w, IMG_BTN_SPIN);
    wheelButton->setScale(WHEEL_SCALE);
    wheelButton->setPositionY( wheelButton->getPositionY()-125 );

    auto resetButton = resetGameButtonInit(w, IMG_BTN_SPIN);
    resetButton->setScale(WHEEL_SCALE - 0.5);
    resetButton->setPosition(resetButton->getPositionX()-30,resetButton->getPositionY()+130);

    auto testButton = testButtonInit(w, IMG_BTN_SPIN);
    testButton->setScale(WHEEL_SCALE - 0.5);
    testButton->setPosition(testButton->getPositionX()+30,testButton->getPositionY()+130);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, wheelButton,resetButton,testButton,/*spinBtn,*/ NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////

    return true;
}

void GameScene::playGame(Wheel* theWheel){

    LOGGER("---Start game---");

    std::string str = "ERROR";
    ItemDrop* prize = theWheel->spin(true);

    if(prize != nullptr)
        str = prize->getName();


    LOGGER("prize is: %s", str.c_str());
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

MenuItemImage *GameScene::resetGameButtonInit(Wheel* theWheel, std::string ImageFileName) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    MenuItemImage* button = MenuItemImage::create(ImageFileName, ImageFileName, CC_CALLBACK_0(GameScene::resetWheelGame, this) );

    Label* txt = Label::createWithTTF("Reset", DEF_FONT, 20);


    button->addChild(txt);
    txt->setPosition(button->getContentSize().width/2, button->getContentSize().height/2 +2);
    txt->enableOutline(cocos2d::Color4B::BLACK, 3);

    button->setPosition(centerScreen);

    return button;
}

void GameScene::resetWheelGame() {
    auto newScene = GameScene::createScene();
    Director::getInstance()->replaceScene(newScene);
}

cocos2d::MenuItemImage* GameScene::testButtonInit(Wheel *theWheel, std::string ImageFileName) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);


    MenuItemImage* button = MenuItemImage::create(ImageFileName, ImageFileName, CC_CALLBACK_0(GameScene::showUnitTests, theWheel ) );


    Label* txt = Label::createWithTTF("debug menu", DEF_FONT, 20);


    button->addChild(txt);
    txt->setPosition(button->getContentSize().width/2, button->getContentSize().height/2 +2);
    txt->enableOutline(cocos2d::Color4B::BLACK, 1);
    button->setPosition(centerScreen);


    return button;

}

void GameScene::showUnitTests(Wheel* theWheel) {
    auto sceneObj = theWheel->getParent();
    Menu* devMenu = dynamic_cast<Menu *>(sceneObj->getChildByName(DEBUG_TAG));

    //if the UnitTestMenu is already showing, this will remove it
    //otherwise the menu will be displayed
    if(devMenu == nullptr) {
        devMenu = UnitTests::createMenu(theWheel);
        devMenu->setScale(0.5);
        devMenu->setPosition(theWheel->getCenterOfWheel());
        sceneObj->addChild(devMenu);

    }else{
        devMenu->setVisible( !devMenu->isVisible() );
    }

    LOGGER("Debug menu: %s",( devMenu->isVisible() ? "ON" :"OFF" ));

}




