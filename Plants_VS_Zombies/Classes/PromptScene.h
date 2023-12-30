#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include "MarketScene.h"
#include <string>

class PromptScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void gotoGameCallback(Ref* pSender);
    void backtoMain(cocos2d::Ref* pSender);

    CREATE_FUNC(PromptScene);
};