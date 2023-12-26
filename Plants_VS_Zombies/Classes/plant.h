//植物类
#ifndef __PLANT_H__
#define __PLANT_H__
#include"Entity.h"
#include "cocos2d.h"

#define PLANT_DEAD 0;
#define PLANT_BEINGEATEN 1;
#define PLANT_HEALTHY 2;

USING_NS_CC;
class Plant : public Entity {
public:

    int getHealth(){ return health; }
    void setHealth(int Health) { health = Health; }

    int getAttackDamage() { return attackDamage; }
    void setAttackDamage(int AttackDamage) { attackDamage = AttackDamage; }

    int getRow() { return row; }
    void setRow(int Row) { row = Row; }

    int getCol() { return col; }
    void setCol(int Col) { col=Col; }

    void setIsSleeping(int i) { isSleeping = i; }
    int getIsSleeping() { return isSleeping; }

    void setCondition(int con) { condition = con;}
    int getCondition() {return condition;}

    void setX(int _x) { x = _x; }
    int getX() { return x; }

    void setY(int _y) { y = _y; }
    int getY() { return y; }

    //几种动画:每种植物必须写
    //virtual void waitingAnimation()=0;//空闲
    //virtual void attackAnimation()=0;//工作
    virtual void dieAnimation(){};//死亡

    //给god使用,返回值为0，说明植物已经死亡，需要从vector中删除该植物
    bool getHurt(int hurtValue) {
        health -= hurtValue;
        if (health <= 0) {
            dieAnimation();
            return 0;
        }
        return 1;
    }

private:
    int health;   //生命值      
    int attackDamage=0;//伤害值
    int isSleeping;//植物是否在睡觉
    int row;//行
    int col;//列
    int condition=PLANT_HEALTHY;//记录状态
    int x;//xy坐标
    int y;
};

#endif // __PLANT_H__

