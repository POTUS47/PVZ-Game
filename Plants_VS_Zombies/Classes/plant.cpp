#include "Plant.h"

Plant::Plant() {}
Plant::~Plant() {}
//���������ڸ����в���ʵ��

bool Plant::init() {
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void Plant::performAction() {
    // ʵ��ֲ��Ļ�����Ϊ�����繥����ʬ
}

void Plant::takeDamage(int damage) {
    // ʵ��ֲ�ﱻ����ʱ�Ĵ���
    // �������ֲ�������ֵ���������˶�����
}

std::string Plant::getType() {
    // ����ֲ������ͣ��������ַ�����ʾ
    return "NormalPlant";
}

//
void Plant::plantAtPosition(const cocos2d::Vec2& position,const cocos2d::Scene* a) {
    // ����ֲ���λ��
    this->setPosition(position);
    // ��ֲ����ӵ�������
    // ���磺Director::getInstance()->getRunningScene()->addChild(this);
}
