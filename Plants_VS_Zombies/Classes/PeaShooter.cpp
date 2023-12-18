// PeaShooter.cpp
#include "PeaShooter.h"

PeaShooter::PeaShooter() {
// 可以在这里进行豌豆射手特有的初始化工作，例如设置特定纹理、属性等
    auto sprite = Sprite::create("zombietest.png");

    
// 设置豌豆射手的生命值、攻击值等属性
    health = 100;
    attackDamage = 20;
}

PeaShooter::~PeaShooter() {}


void PeaShooter::performAction() {
    // 重写攻击行为，实现射手植物的射击逻辑
    // 在这里可以调用发射子弹的方法
    shoot();
}

std::string PeaShooter::getType() {
    // 获取射手植物的类型
    return "PeaShooter";
}

// 可以在这里实现射手植物特有的行为和方法

