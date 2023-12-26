//植物类
#ifndef __PLANT_H__
#define __PLANT_H__
#include"Entity.h"
#include "cocos2d.h"
    //检查发现，横向总共1920
    /* 植物的位置 纵坐标分别是160 350 540 730 920比较好（等差190）
    * 横坐标分别是 215 405...（等差190）
    * 植物的row=(y-160)/190+1
    */

USING_NS_CC;
class Plant : public Entity {
public:

    int getHealth() { return health; }
    void setHealth(int Health) { health = Health; }

    int getAttackDamage() { return attackDamage; }
    void setAttackDamage(int AttackDamage) { attackDamage = AttackDamage; }

    int getRow() { return row; }
    void setRow(int Row) { row = Row; }

    int getCol() { return col; }
    void setCol(int Col) { col = Col; }

    void setCondition(int con) { condition = con; }
    int getCondition() { return condition; }

    void setX(int _x) { x = _x; }
    int getX() { return x; }

    void setY(int _y) { y = _y; }
    int getY() { return y; }


    //几种动画:每种植物必须写
    //virtual void waitingAnimation()=0;//空闲
    //virtual void attackAnimation()=0;//工作
    virtual void dieAnimation() {};//死亡

    //植物受伤
    void getHurt(int hurtValue) {
        health -= hurtValue;
    }

    void setName(int n) { name = n; }
    int getName() { return name; }

private:
    int name;//记录是何种植物,方便发射相应的子弹
    int health;   //生命值      
    int attackDamage = 0;//单发子弹伤害值
    int row;//行
    int col;//列
    int condition = HEALTHY;//记录状态
    int x;//xy坐标
    int y;
};

#endif // __PLANT_H__


