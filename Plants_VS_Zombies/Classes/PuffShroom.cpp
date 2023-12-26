#include "PuffShroom.h"

PuffShroom::PuffShroom(int x, int y, double scale, Scene* scene, int isNight) {
    setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
    setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
    setX(x);
    setY(y);
    setName(PUFF_SHROOM);
    auto puffshroom = cocos2d::Sprite::create("/plant/puffshroom/w (1).png");
    puffshroom->setPosition(x, y);
    puffshroom->setScale(scale);
    //���ӵ���ǰ��
    scene->addChild(puffshroom, 2);
    setIdv(puffshroom);//������ָ�����idv

    //��������ֵ������
    setHealth(100);
    setAttackDamage(10);
    //��ֲ�￪ʼҡ��
    if (isNight)
        attackAnimation();
    else
        waitingAnimation();
}

//ֲ��Ŀ���ҡ�ڶ���
void PuffShroom::waitingAnimation() {
    this->setCondition(PLANT_SLEEP);
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 11; i++)
    {
        sprintf(nameSize, "/plant/puffshroom/s (%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻�������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ��Ĺ�������
void PuffShroom::attackAnimation() {
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 15; i++)
    {
        sprintf(nameSize, "/plant/puffshroom/w (%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻�������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���

}

//ֲ����������ʧ
void PuffShroom::dieAnimation() {
    this->setCondition(DEAD);
    getIdv()->setVisible(false);
    //this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}


