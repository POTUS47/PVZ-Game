#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include "MarketScene.h"
#include <string>

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void replaceSceneCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

