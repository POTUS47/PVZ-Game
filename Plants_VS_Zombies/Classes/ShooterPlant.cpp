// ShooterPlant.cpp
#include "ShooterPlant.h"

ShooterPlant::ShooterPlant() {
    // �����������������ֲ�����еĳ�ʼ�����������������ض��������Ե�
}

ShooterPlant::~ShooterPlant() {}

bool ShooterPlant::init() {
    if (!Plant::init()) {
        return false;
    }

    // ��������Խ�������ֲ�����еĳ�ʼ�����������������ض��������Ե�

    return true;
}

void ShooterPlant::performAction() {
    // ��д������Ϊ��ʵ������ֲ�������߼�
    shoot();
}

std::string ShooterPlant::getType() {
    // ��ȡ����ֲ�������
    return "ShooterPlant";
}

void ShooterPlant::shoot() {
    // ����ֲ��������߼������紴���ӵ�������
}
