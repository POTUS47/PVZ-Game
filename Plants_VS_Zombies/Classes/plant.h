//ֲ����
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

    //���ֶ���:ÿ��ֲ�����д
    //virtual void waitingAnimation()=0;//����
    //virtual void attackAnimation()=0;//����
    virtual void dieAnimation(){};//����

    //��godʹ��,����ֵΪ0��˵��ֲ���Ѿ���������Ҫ��vector��ɾ����ֲ��
    bool getHurt(int hurtValue) {
        health -= hurtValue;
        if (health <= 0) {
            dieAnimation();
            return 0;
        }
        return 1;
    }

private:
    int health;   //����ֵ      
    int attackDamage=0;//�˺�ֵ
    int isSleeping;//ֲ���Ƿ���˯��
    int row;//��
    int col;//��
    int condition=PLANT_HEALTHY;//��¼״̬
    int x;//xy����
    int y;
};

#endif // __PLANT_H__

