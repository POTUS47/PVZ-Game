#pragma once
#include "cocos2d.h"
#include "Main_menu.h"

class AchievementScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void gotoGameCallback(Ref* pSender);
    void backtoMain(cocos2d::Ref* pSender);

    CREATE_FUNC(AchievementScene);
};
