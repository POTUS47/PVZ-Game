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
    bool canCreateSun() { return CanCreateSun; }
    void setCanCreateSun() { CanCreateSun = 1; }
    void setCanNotCreateSun() { CanCreateSun = 0; }//设为不能产阳光

    bool IsHealthy() { return !(health < 0); }

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

    void setEatCondition(int con) { eatCondition = con; }
    int getEatCondition() { return eatCondition; }

    void setX(int _x) { x = _x; }
    int getX() { return x; }

    void setY(int _y) { y = _y; }
    int getY() { return y; }

    bool IsAdolescent() { return isAdolescent; }
    void setAdolescent(bool i) { isAdolescent = i; }

    long long int getPlantTime() { return plantTime; }//获取植物种植时间
    void setPlantTime(long long int t) { plantTime = t; }

    //几种动画:每种植物必须写
    virtual void waitingAnimation(){};//空闲
    virtual void attackAnimation() {};//工作

    virtual void growUp(){}//用于特殊植物的生长

    //植物受伤
    void getHurt(int hurtValue) {
        health -= hurtValue;
        if (!IsHealthy())
            dieAnimation();
    }

    void setName(int n) { name = n; }
    int getName() { return name; }

    //植物死亡：消失
    void dieAnimation() {
        this->setCondition(DEAD);
        getIdv()->setVisible(false);
        //this->getIdv()->removeFromParent();//让植物立刻消失在画面中
    }

private:
    bool CanCreateSun = 1;//针对能产阳光的特殊植物

    int eatCondition = NOT_EATEN;

    int name;//记录是何种植物,方便发射相应的子弹
    int health;   //生命值      
    int attackDamage = 0;//单发子弹伤害值
    int row;//行
    int col;//列
    int condition = HEALTHY;//记录状态
    int x;//xy坐标
    int y;
    bool isAdolescent = 1;//植物处于幼年期 用于阳光菇的生长
    long long int plantTime;//记录植物的种植时间
};

#endif // __PLANT_H__


