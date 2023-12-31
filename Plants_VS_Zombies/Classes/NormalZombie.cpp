#include"NormalZombie.h"
USING_NS_CC;

//普通僵尸的构造函数
//传入起始位置 缩放大小
normalZombie::normalZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(20);
    setWeapen(false);//普通僵尸没有武器
    setCondition(WAIT);
    setHP(100);
    setAttack(2);
    setEatingTime(1.0f);
    auto normalzombie = cocos2d::Sprite::create("/normalzombie/standgif/1.png");
    normalzombie->setPosition(x, y);
    normalzombie->setScale(scale);
    //添加到当前层
    scene->addChild(normalzombie, 2);
    setIdv(normalzombie);//将精灵指针存入idv
}

void normalZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void normalZombie::healthyEating(Sprite* who) 
{
    who->stopAllActions();
    auto animation = Animation::create();
    char healthyattackarray[40] = { 0 };
    /*僵尸吃植物*/
    for (int i = 1; i < 22; i++)
    {
        sprintf(healthyattackarray, "/normalzombie/healthyattack/%d.png", i);
        animation->addSpriteFrameWithFile(healthyattackarray);
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
void normalZombie::moveForward(Sprite* who)
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
    /*走路前进gif*/
    for (int i = 1; i < 30; i++)
    {
        sprintf(nameSize, "/normalzombie/moveforwardgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);//设置动画帧频率
    animation->setLoops(-1);//设置播放循环 一直播放 为-1
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto animate = Animate::create(animation);
    who->runAction(animate);
}


void normalZombie::moveWithoutArm(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize1[40] = { 0 };
    /*断胳膊向前走*/
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize1, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize1);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim2 = Animate::create(animation);
}




void normalZombie::dieAndlay(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
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
    who->runAction(anim);
    

}




//头掉动画
void normalZombie::loseHead(Sprite* who)
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

