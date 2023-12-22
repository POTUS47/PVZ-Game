//ֲ����
#ifndef __PLANT_H__
#define __PLANT_H__
#include"Entity.h"
#include "cocos2d.h"
USING_NS_CC;
class Plant : public Entity {
public:

    int getHealth(){ return health; }
    int getAttackDamage() { return attackDamage; }
    void setHealth(int Health) { health = Health; }
    void setAttackDamage(int AttackDamage) { attackDamage = AttackDamage; }
    int getRow() { return row; }
    void setRow(int Row) { row = Row; }
    int getCol() { return col; }
    void setCol(int Col) { col=Col; }
    void setIsSleeping(int i) { isSleeping = i; }

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
    int attackDamage;//�˺�ֵ
    int isSleeping;//ֲ���Ƿ���˯��
    int row;//��
    int col;//��
};

#endif // __PLANT_H__

