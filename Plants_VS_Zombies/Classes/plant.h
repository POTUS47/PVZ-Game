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
    bool canCreateSun() { return CanCreateSun; }
    void setCanCreateSun() { CanCreateSun = 1; }
    void setCanNotCreateSun() { CanCreateSun = 0; }//��Ϊ���ܲ�����

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

    long long int getPlantTime() { return plantTime; }//��ȡֲ����ֲʱ��
    void setPlantTime(long long int t) { plantTime = t; }

    //���ֶ���:ÿ��ֲ�����д
    virtual void waitingAnimation(){};//����
    virtual void attackAnimation() {};//����

    virtual void growUp(){}//��������ֲ�������

    //ֲ������
    void getHurt(int hurtValue) {
        health -= hurtValue;
        if (!IsHealthy())
            dieAnimation();
    }

    void setName(int n) { name = n; }
    int getName() { return name; }

    //ֲ����������ʧ
    void dieAnimation() {
        this->setCondition(DEAD);
        getIdv()->setVisible(false);
        //this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
    }

private:
    bool CanCreateSun = 1;//����ܲ����������ֲ��

    int eatCondition = NOT_EATEN;

    int name;//��¼�Ǻ���ֲ��,���㷢����Ӧ���ӵ�
    int health;   //����ֵ      
    int attackDamage = 0;//�����ӵ��˺�ֵ
    int row;//��
    int col;//��
    int condition = HEALTHY;//��¼״̬
    int x;//xy����
    int y;
    bool isAdolescent = 1;//ֲ�ﴦ�������� �������⹽������
    long long int plantTime;//��¼ֲ�����ֲʱ��
};

#endif // __PLANT_H__


