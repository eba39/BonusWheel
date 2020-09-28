/*
*     AUTHOR: ERIK ALMAGUER
*     FILE: GameScene.h
*     Description: This class holds the code for the main scene of the game.
*
*
*
*/

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "WheelMaker.h"
USING_NS_CC;

class GameScene : public cocos2d::Scene
{
private:
    MenuItemImage* closeButtonInit();
    MenuItemImage* resetGameButtonInit(Wheel* theWheel, std::string ImageFileName);
    MenuItemImage* createPlayButton(Wheel* theWheel, std::string ImageFileName);
    MenuItemImage* testButtonInit(Wheel *theWheel, std::string ImageFileName);


    static void showUnitTests(Wheel* theWheel);
    static void playGame(Wheel* theWheel);


public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);
    void resetWheelGame();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


};

#endif //  __GAME_SCENE_H__
