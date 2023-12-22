// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter(int row,int col,Scene* scene) {
// 可以在这里进行豌豆射手特有的初始化工作，例如设置特定纹理、属性等
    auto sprite = Sprite::create("zombietest.png");
    setRow(row);
    setCol(col);
    sprite->setPosition(Vec2(row, col));
    sprite->setScale(1, 1);//到时候调
    scene->addChild(sprite);
// 设置豌豆射手的生命值、攻击值等属性
    setHealth(100);
    setAttackDamage(20);

    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    normalzombie->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

PeaShooter::~PeaShooter() {}



void PeaShooter::performAction() {
    // 重写攻击行为，实现射手植物的射击逻辑
    // 在这里可以调用发射子弹的方法
    shoot();
}

std::string PeaShooter::getType() {
    // 获取射手植物的类型
    return "PeaShooter";
}

// 可以在这里实现射手植物特有的行为和方法

