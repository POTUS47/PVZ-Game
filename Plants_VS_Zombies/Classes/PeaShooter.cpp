// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter() {
// ��������������㶹�������еĳ�ʼ�����������������ض��������Ե�
    auto sprite = Sprite::create("zombietest.png");

    
// �����㶹���ֵ�����ֵ������ֵ������
    health = 100;
    attackDamage = 20;
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

