#include "puffShroomBullet.h"

USING_NS_CC;

puffShroomBullet::puffShroomBullet(int scale,int _row, int startX, int startY, int bulletDamage, Scene* scene) :Bullet(_row,startX, startY, bulletDamage, scene)
{
    auto bullet = cocos2d::Sprite::create("/plant/shroombullet/s (1).png");
    bullet->setPosition(startX, startY); 
    bullet->setScale(scale);
    setRow(_row);
    //添加到当前层
    scene->addChild(bullet, 6);
    setIdv(bullet);//将精灵指针存入idv

    //子弹运动动画
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 7; i++)
    {
        sprintf(nameSize, "/plant/shroombullet/s (%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.2f);//设置每帧播放的时间间隔
    animation->setLoops(1);//设置动画播放的循环次数
    auto animate = Animate::create(animation);//创建动画动作
    auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create(animate, CallFunc::create([=]() {
        bullet->removeFromParent(); // 移动完成后移除子弹
        }), callFunc2, nullptr);
    bullet->runAction(sequence);
}

//子弹播放爆炸特效并消失
void puffShroomBullet::explodeAnimation() {

}
