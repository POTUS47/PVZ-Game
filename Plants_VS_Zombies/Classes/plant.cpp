#include "Plant.h"

Plant::Plant() {}
Plant::~Plant() {}
//构造析构在父类中不予实现

bool Plant::init() {
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void Plant::performAction() {
    // 实现植物的基本行为，例如攻击僵尸
}

void Plant::takeDamage(int damage) {
    // 实现植物被攻击时的处理
    // 例如减少植物的生命值，播放受伤动画等
}

std::string Plant::getType() {
    // 返回植物的类型，可以是字符串表示
    return "NormalPlant";
}

//
void Plant::plantAtPosition(const cocos2d::Vec2& position,const cocos2d::Scene* a) {
    // 设置植物的位置
    this->setPosition(position);
    // 将植物添加到场景中
    // 例如：Director::getInstance()->getRunningScene()->addChild(this);
}
