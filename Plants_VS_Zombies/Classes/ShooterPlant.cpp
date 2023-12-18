// ShooterPlant.cpp
#include "ShooterPlant.h"

ShooterPlant::ShooterPlant() {
    // 可以在这里进行射手植物特有的初始化工作，例如设置特定纹理、属性等
}

ShooterPlant::~ShooterPlant() {}

bool ShooterPlant::init() {
    if (!Plant::init()) {
        return false;
    }

    // 在这里可以进行射手植物特有的初始化工作，例如设置特定纹理、属性等

    return true;
}

void ShooterPlant::performAction() {
    // 重写攻击行为，实现射手植物的射击逻辑
    shoot();
}

std::string ShooterPlant::getType() {
    // 获取射手植物的类型
    return "ShooterPlant";
}

void ShooterPlant::shoot() {
    // 射手植物射击的逻辑，例如创建子弹并发射
}
