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

    virtual bool init();
    void gotoMenu(Ref* pSender);

    CREATE_FUNC(MiniGame);
};