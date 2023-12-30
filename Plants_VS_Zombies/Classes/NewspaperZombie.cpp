#include"NewspaperZombie.h"
USING_NS_CC;

//报纸僵尸的构造函数
//传入起始位置 缩放大小
newspaperZombie::newspaperZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(30);
    setWeapen(true);//有报纸
    setCondition(WAIT);
    setHP(80);
    setAttack(10);
    setEatingTime(1.2f);
    auto normalzombie = cocos2d::Sprite::create("/newspaperzombie/wait/1.png");
    normalzombie->setPosition(x, y);
    normalzombie->setScale(scale);
    //添加到当前层
    scene->addChild(normalzombie, 2);
    setIdv(normalzombie);//将精灵指针存入idv
}

void newspaperZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 20; i++)
    {
        sprintf(nameSize, "/newspaperzombie/wait/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void newspaperZombie::healthyEating(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();

    char healthyattackarray[50] = { 0 };
    if (getWeapen() == true) {//如果现在还有武器
        for (int i = 1; i < 9; i++)
        {
            sprintf(healthyattackarray, "/newspaperzombie/paperattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    else {//如果没武器了（帽子掉了）
        for (int i = 1; i < 8; i++)
        {
            sprintf(healthyattackarray, "/newspaperzombie/withoutpaperattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
        setEatingTime(0.7f);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);//循环播放
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BGM/newspaper.mp3");
}

/**
* @param 传入是哪个精灵要向前走
* @return void
*/
void newspaperZombie::moveForward(Sprite* who)
{
    if (getCondition() == WAIT) {//如果是从等待区改为向前走
        int starty = getCol();
        who->setPosition(1950, starty * 200 - 10);//需要设置出发位置
    }
    setCondition(WALKING);
    who->stopAllActions();
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    if (getWeapen() == true) {//如果现在还有武器
        for (int i = 1; i < 20; i++)
        {
            sprintf(nameSize, "/newspaperzombie/paperwalk/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
        auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
        who->runAction(moveBy);
    }
    else {//如果没武器了（帽子掉了）
        for (int i = 1; i < 15; i++)
        {
            sprintf(nameSize, "/newspaperzombie/withoutpaperwalk/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
        setSpeed(70);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BGM/newspaper.mp3");
        auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
        who->runAction(moveBy);
    }
    animation->setDelayPerUnit(0.1f);//设置动画帧频率
    animation->setLoops(-1);//设置播放循环 一直播放 为-1
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto animate = Animate::create(animation);
    who->runAction(animate);
   
}

void newspaperZombie::dieAndlay(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
    char diearray[40] = { 0 };
    /*僵尸死亡趴下*/
    for (int i = 1; i < 12; i++)
    {
        sprintf(diearray, "/newspaperzombie/die/%d.png", i);
        animation->addSpriteFrameWithFile(diearray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//只播放一次
    animation->setRestoreOriginalFrame(true);//动画结束后恢复到第一帧
    auto anim = Animate::create(animation);
    who->runAction(anim);


}




//头掉动画
void newspaperZombie::loseHead(Sprite* who)
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

