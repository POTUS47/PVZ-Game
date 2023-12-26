//ֲ����
#ifndef __PLANT_H__
#define __PLANT_H__
#include"Entity.h"
#include "cocos2d.h"
    //��鷢�֣������ܹ�1920
    /* ֲ���λ�� ������ֱ���160 350 540 730 920�ȽϺã��Ȳ�190��
    * ������ֱ��� 215 405...���Ȳ�190��
    * ֲ���row=(y-160)/190+1
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


    //���ֶ���:ÿ��ֲ�����д
    //virtual void waitingAnimation()=0;//����
    //virtual void attackAnimation()=0;//����
    virtual void dieAnimation() {};//����

    //ֲ������
    void getHurt(int hurtValue) {
        health -= hurtValue;
    }

    void setName(int n) { name = n; }
    int getName() { return name; }

private:
    int name;//��¼�Ǻ���ֲ��,���㷢����Ӧ���ӵ�
    int health;   //����ֵ      
    int attackDamage = 0;//�����ӵ��˺�ֵ
    int row;//��
    int col;//��
    int condition = HEALTHY;//��¼״̬
    int x;//xy����
    int y;
};

#endif // __PLANT_H__


