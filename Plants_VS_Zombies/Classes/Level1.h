#pragma once
#include "cocos2d.h"
#include"God.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>
#include<vector>


class God;
class Level1 : public cocos2d::Scene
{
private:
    God* god; //上帝的实例化
    Sprite* background;//背景的指针
    Layer* choose;//选择植物层的指针
    Label* sunlightLabel;
    bool GameStart = false;//游戏是否开始了？
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void goBackMain(cocos2d::Ref* pSender);
    void onMoveByFinished();
    void update(float dt);
    void moveRight(Ref* sender);//场景和僵尸向右移动
    void startChoose();

    CREATE_FUNC(Level1);
};