#include "DoubleShooter.h"

DoubleShooter::DoubleShooter(int x, int y, double scale, Scene* scene) {
    setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
    auto doubleShooter = cocos2d::Sprite::create("/plant/doubleshooter/Repeater1.png");
    doubleShooter->setPosition(x, y);
    doubleShooter->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(doubleShooter, 2);
    setIdv(doubleShooter);//������ָ�����idv

    //��������ֵ������
    setHealth(100);
    setAttackDamage(9);
    /////////////////////////��ֲ�￪ʼҡ��
    waitingAnimation();
}

//ֲ��Ŀ���ҡ�ڶ���
void DoubleShooter::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/doubleshooter/Repeater%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ��Ĺ�������
void DoubleShooter::attackAnimation() {
    ///////////////////////////////////////////////////////////��û��д
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/nut/zz%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ����������ʧ
void DoubleShooter::dieAnimation() {
    this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}
