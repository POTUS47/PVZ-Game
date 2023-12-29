#pragma once
#include "cocos2d.h"
#include"God.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>
#include<vector>
#include"Sun.h"


class God;
class Level : public cocos2d::Scene
{
private:
    God* god; //上帝的实例化
    Sun* sun;
    Sprite* background;//背景的指针
    Layer* choose;//选择植物层的指针
    Label* sunlightLabel;
    bool GameStart = false;//游戏是否开始了？

    //


public:
    virtual void Level::SetBackground()=0;//添加背景图片
    /*示例：    background = Sprite::create("/level1/bg.jpg");
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);*/
    virtual bool init();//可以在其中增添特殊初始化需求
    static cocos2d::Scene* createScene();
    void update(float dt);
    void CheckEveryMin(float dt);
    void goBackMain(cocos2d::Ref* pSender);
    void CheckEveryTwoSec(float dt);

    void onMoveByFinished();

    void moveRight(Ref* sender);//场景和僵尸向右移动
    virtual void startChoose();//一般不需要重新写



    CREATE_FUNC(Level);
};
