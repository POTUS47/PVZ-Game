#include "DoubleShooter.h"

DoubleShooter::DoubleShooter(int x, int y, double scale, Scene* scene) {
    setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
    auto doubleShooter = cocos2d::Sprite::create("/plant/doubleshooter/Repeater1.png");
    doubleShooter->setPosition(x, y);
    doubleShooter->setScale(scale);
    //添加到当前层
    scene->addChild(doubleShooter, 2);
    setIdv(doubleShooter);//将精灵指针存入idv

    //设置生命值等属性
    setHealth(100);
    setAttackDamage(9);
    /////////////////////////让植物开始摇摆
    waitingAnimation();
}

//植物的空闲摇摆动画
void DoubleShooter::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/doubleshooter/Repeater%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//植物的攻击动画
void DoubleShooter::attackAnimation() {
    ///////////////////////////////////////////////////////////还没有写
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/nut/zz%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//植物死亡：消失
void DoubleShooter::dieAnimation() {
    this->getIdv()->removeFromParent();//让植物立刻消失在画面中
}
