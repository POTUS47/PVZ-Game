#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include "MarketScene.h"
#include <string>

class MiniGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    void onExit();
    virtual bool init();

    CREATE_FUNC(MiniGame);
};