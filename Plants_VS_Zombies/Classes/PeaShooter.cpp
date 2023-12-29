// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter(int x,int y, double scale,Scene* scene) {
    auto nut = cocos2d::Sprite::create("/plant/peashooter/Peashooter1.png");
    nut->setPosition(x, y);
    nut->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(nut, 2);
    setIdv(nut);//������ָ�����idv

    //��������ֵ������
    setHealth(100);
<<<<<<< Updated upstream
    setAttackDamage(9);
    /////////////////////////��ֲ�￪ʼҡ��
=======
    setAttackDamage(10);
    //ֲ�����ȴ�����
>>>>>>> Stashed changes
    waitingAnimation();
}

//ֲ��Ŀ���ҡ�ڶ���
void PeaShooter::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/peashooter/Peashooter%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ��Ĺ�������
void PeaShooter::attackAnimation() {
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
void PeaShooter::dieAnimation() {
    this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}



