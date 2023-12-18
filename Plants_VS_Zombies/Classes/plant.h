//植物类
#ifndef __PLANT_H__
#define __PLANT_H__

#include "cocos2d.h"

class Plant : public cocos2d::Sprite {
public:
    Plant();
    virtual ~Plant();

    // 植物的基本行为，例如攻击僵尸
    virtual void performAction();

    // 植物被攻击时的处理
    virtual void takeDamage(int damage);

    // 获取植物的类型
    virtual std::string getType();

    // 放置植物在指定位置
    void plantAtPosition(const cocos2d::Vec2& position, const cocos2d::Scene* a);

    // 获取植物的生命值
    int getHealth() const { return health; }

    // 获取植物的攻击值
    int getAttackDamage() const { return attackDamage; }

    // 获取植物的位置
    cocos2d::Vec2 GetPosition() const { return this->getPosition(); }


    int health;         
    int attackDamage;

};

#endif // __PLANT_H__

