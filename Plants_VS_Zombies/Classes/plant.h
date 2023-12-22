//植物类
#ifndef __PLANT_H__
#define __PLANT_H__

#include "cocos2d.h"
USING_NS_CC;
class Plant : public cocos2d::Sprite {
public:
    Plant();
    ~Plant();

    // 植物的基本行为，例如攻击僵尸
    virtual void working()=0;
    // 植物被攻击时的处理
    virtual void attacked(int damage)=0;

    // 放置植物在指定位置
    void plantAtPosition(const cocos2d::Vec2& position, const cocos2d::Scene* a);


    int getHealth(){ return health; }
    int getAttackDamage() { return attackDamage; }
    void setHealth(int Health) { health = Health; }
    void setAttackDamage(int AttackDamage) { attackDamage = AttackDamage; }
    bool isWorkig() { return (health > 0); }
    int getRow() { return row; }
    int setRow(int Row) { row = Row; }
    int getCol() { return col; }
    int setCol(int Col) { col=Col; }
private:
    int health;   //生命值      
    int attackDamage;//伤害值
    int row;//行
    int col;//列
};

#endif // __PLANT_H__

