#include "flame.h"

USING_NS_CC;

Flame::Flame(int row, int startX, int startY, int bulletDamage, Scene* scene) :Bullet(row, startX, startY, bulletDamage, scene)
{
    auto bullet = cocos2d::Sprite::create("/plant/flame/h (1).png");
    bullet->setPosition(960, startY);//在该行的中间开始爆炸
    bullet->setScale(2);
    //添加到当前层
    scene->addChild(bullet, 6);
    setIdv(bullet);//将精灵指针存入idv

    //子弹运动动画
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/flame/h (%d).png", 9-i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(1);//设置动画播放的循环次数
    auto animate = Animate::create(animation);//创建动画动作
    auto sequence = Sequence::create(animate, CallFunc::create([=]() {
        bullet->removeFromParent(); // 移动完成后移除子弹
        }), nullptr);
    bullet->runAction(sequence);
}
