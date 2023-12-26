// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter(int x,int y, double scale,Scene* scene) {
    setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
    setCol((x - 215) / 190 + 1);//设置植物在哪一列出现
    setX(x);
    setY(y);
    setName(PEA_SHOOTER);
    auto nut = cocos2d::Sprite::create("/plant/peashooter/Peashooter1.png");
    nut->setPosition(x, y);
    nut->setScale(scale);
    //添加到当前层
    scene->addChild(nut, 2);
    setIdv(nut);//将精灵指针存入idv

    //设置生命值等属性
    setHealth(100);
    setAttackDamage(1);
    //植物进入等待动画
    waitingAnimation();
}

//植物的空闲摇摆动画
void PeaShooter::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/peashooter/Peashooter%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//植物死亡：消失
void PeaShooter::dieAnimation() {
    this->getIdv()->removeFromParent();//让植物立刻消失在画面中
}



