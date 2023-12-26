#include "FumeShroom.h"

FumeShroom::FumeShroom(int x, int y, double scale, Scene* scene,int isNight) {
    setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
    setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
    setX(x);
    setY(y);
    setName(FUME_SHROOM);
    auto puffshroom = cocos2d::Sprite::create("/plant/fumeshroom/w(1).png");
    puffshroom->setPosition(x, y);
    puffshroom->setScale(scale);
    //��ӵ���ǰ��
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
void FumeShroom::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 15; i++)
    {
        sprintf(nameSize, "/plant/fumeshroom/s(%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ��Ĺ�������
void FumeShroom::attackAnimation() {
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/fumeshroom/w(%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���

}

//ֲ����������ʧ
void FumeShroom::dieAnimation() {
    this->setCondition(DEAD);//��god��ǩ������ɾ��ֲ��
    getIdv()->setVisible(false);
    //this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}



