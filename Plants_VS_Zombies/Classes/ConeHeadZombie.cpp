#include"ConeHeadZombie.h"
USING_NS_CC;

//圆锥僵尸的构造函数
//传入起始位置 缩放大小
coneHeadZombie::coneHeadZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(30);
    setWeapen(true);
    setCondition(WAIT);
    setHP(120);
    setAttack(25);
    setEatingTime(0.8f);
    auto conezombie = cocos2d::Sprite::create("/conehead/standby/1.png");
    conezombie->setPosition(x, y);
    conezombie->setScale(scale);
    //添加到当前层
    scene->addChild(conezombie, 2);
    setIdv(conezombie);//将精灵指针存入idv
}

void coneHeadZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/conehead/standby/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void coneHeadZombie::healthyEating(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
    
    char healthyattackarray[40] = { 0 };
    if (getWeapen() == true) {//如果现在还有武器
        for (int i = 1; i < 12; i++)
        {
            sprintf(healthyattackarray, "/conehead/healthyeating/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    else {//如果没武器了（帽子掉了）
        for (int i = 1; i < 22; i++)
        {
            sprintf(healthyattackarray, "/normalzombie/healthyattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);//循环播放
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);
}

/**
* @param 传入是哪个精灵要向前走
* @return void
*/
void coneHeadZombie::moveForward(Sprite* who)
{
    if (getCondition() == WAIT) {//如果是从等待区改为向前走
        int starty = getCol();
        who->setPosition(1950, starty * 200 - 10);//需要设置出发位置
    }
    setCondition(WALKING);
    who->stopAllActions();
    auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
    who->runAction(moveBy);
    auto animation = Animation::create();
    char nameSize[40] = { 0 };
    if (getWeapen() == true) {//如果现在还有武器
        for (int i = 1; i < 22; i++)
        {
            sprintf(nameSize, "/conehead/walking/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    }
    else {//如果没武器了（帽子掉了）
        for (int i = 1; i < 30; i++)
        {
            sprintf(nameSize, "/normalzombie/moveforwardgif/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    }
    animation->setDelayPerUnit(0.15f);//设置动画帧频率
    animation->setLoops(-1);//设置播放循环 一直播放 为-1
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto animate = Animate::create(animation);
    who->runAction(animate);
}


void coneHeadZombie::dieAndlay(Sprite* who)
{
    auto animation = Animation::create();
    who->stopAllActions();
    char diearray[40] = { 0 };
    /*僵尸死亡趴下*/
    for (int i = 1; i < 11; i++)
    {
        sprintf(diearray, "/normalzombie/die/%d.png", i);
        animation->addSpriteFrameWithFile(diearray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//只播放一次
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);/////////////////////考虑变成返回anim指针？
    
}

//头掉动画
void coneHeadZombie::loseHead(Sprite* who)
{
    auto animation = Animation::create();
    char loseheadarray[40] = { 0 };
    /*僵尸失去头*/
    for (int i = 1; i < 13; i++)
    {
        sprintf(loseheadarray, "/normalzombie/losehead/%d.png", i);
        animation->addSpriteFrameWithFile(loseheadarray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//只播放一次
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);
}