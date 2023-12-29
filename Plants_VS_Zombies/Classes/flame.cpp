#include "flame.h"

USING_NS_CC;

Flame::Flame(int row, int startX, int startY, int bulletDamage, Scene* scene) :Bullet(row, startX, startY, bulletDamage, scene)
{
    auto bullet = cocos2d::Sprite::create("/plant/flame/h (1).png");
    bullet->setPosition(960, startY);//�ڸ��е��м俪ʼ��ը
    bullet->setScale(2);
    //��ӵ���ǰ��
    scene->addChild(bullet, 6);
    setIdv(bullet);//������ָ�����idv

    //�ӵ��˶�����
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/flame/h (%d).png", 9-i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(1);//���ö������ŵ�ѭ������
    auto animate = Animate::create(animation);//������������
    auto sequence = Sequence::create(animate, CallFunc::create([=]() {
        bullet->removeFromParent(); // �ƶ���ɺ��Ƴ��ӵ�
        }), nullptr);
    bullet->runAction(sequence);
}
