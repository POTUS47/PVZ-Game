// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter(int row,int col,Scene* scene) {
// ��������������㶹�������еĳ�ʼ�����������������ض��������Ե�
    auto sprite = Sprite::create("zombietest.png");
    setRow(row);
    setCol(col);
    sprite->setPosition(Vec2(row, col));
    sprite->setScale(1, 1);//��ʱ���
    scene->addChild(sprite);
// �����㶹���ֵ�����ֵ������ֵ������
    setHealth(100);
    setAttackDamage(20);

    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    normalzombie->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

PeaShooter::~PeaShooter() {}



void PeaShooter::performAction() {
    // ��д������Ϊ��ʵ������ֲ�������߼�
    // ��������Ե��÷����ӵ��ķ���
    shoot();
}

std::string PeaShooter::getType() {
    // ��ȡ����ֲ�������
    return "PeaShooter";
}

// ����������ʵ������ֲ�����е���Ϊ�ͷ���

