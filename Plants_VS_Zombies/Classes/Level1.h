#pragma once
#include "cocos2d.h"

class Level1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void goBackMain(cocos2d::Ref* pSender);
    void onMoveByFinished();
    // implement the "static create()" method manually
    CREATE_FUNC(Level1);
};