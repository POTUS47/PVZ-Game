#include "puffShroomBullet.h"

USING_NS_CC;

puffShroomBullet::puffShroomBullet(int scale,int _row, int startX, int startY, int bulletDamage, Scene* scene) :Bullet(_row,startX, startY, bulletDamage, scene)
{
    auto bullet = cocos2d::Sprite::create("/plant/shroombullet/s (1).png");
    bullet->setPosition(startX, startY); 
    bullet->setScale(scale);
    setRow(_row);
    //��ӵ���ǰ��
    scene->addChild(bullet, 6);
    setIdv(bullet);//������ָ�����idv

    //�ӵ��˶�����
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 7; i++)
    {
        sprintf(nameSize, "/plant/shroombullet/s (%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.2f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(1);//���ö������ŵ�ѭ������
    auto animate = Animate::create(animation);//������������
    auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create(animate, CallFunc::create([=]() {
        bullet->removeFromParent(); // �ƶ���ɺ��Ƴ��ӵ�
        }), callFunc2, nullptr);
    bullet->runAction(sequence);
}

//�ӵ����ű�ը��Ч����ʧ
void puffShroomBullet::explodeAnimation() {

}
