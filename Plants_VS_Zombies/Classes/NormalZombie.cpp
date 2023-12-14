#include"cocos2d.h"
#include"Zombie.h"
#include"NormalZombie.h"
USING_NS_CC;

Sprite* normalZombie:: generateOne(Scene* scene) 
{
	auto normalzombie = cocos2d::Sprite::create("/normalzombie/standgif/1.png");
	normalzombie->setPosition(1200, 500);
    normalzombie->setScale(2.0);
    //添加到当前层
    scene->addChild(normalzombie, 0);
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
    normalzombie->runAction(animate);
    return normalzombie;
}

/**
* @param 传入是哪个精灵要向前走
* @return void
*/
void normalZombie::moveForward(Sprite* who)
{
    auto ani2 = Animation::create();
    char nameSize1[40] = { 0 };
    /*diergedongzuof*/
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize1, "/normalzombie/standgif/%d.png", i);
        ani2->addSpriteFrameWithFile(nameSize1);
    }
    ani2->setDelayPerUnit(0.15f);
    ani2->setLoops(1);
    ani2->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim2 = Animate::create(ani2);
    who->runAction(anim2);

    who->stopAllActions();

    auto moveBy = MoveBy::create(2000 / this->getSpeed(), Vec2(-2000, 0));
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

void normalZombie::die(Sprite* who)
{
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
    who->runAction(anim);/////////////////////考虑变成返回anim指针？
}

void normalZombie::healthyAttack(Sprite* who)
{
    auto animation = Animation::create();
    char healthyattackarray[40] = { 0 };
    /*僵尸吃植物*/
    for (int i = 1; i < 22; i++)
    {
        sprintf(healthyattackarray, "/normalzombie/healthyattack/%d.png", i);
        animation->addSpriteFrameWithFile(healthyattackarray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);//只播放一次
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);
}

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