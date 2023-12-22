//ֲ����
#ifndef __PLANT_H__
#define __PLANT_H__

#include "cocos2d.h"
USING_NS_CC;
class Plant : public cocos2d::Sprite {
public:
    Plant();
    ~Plant();

    // ֲ��Ļ�����Ϊ�����繥����ʬ
    virtual void working()=0;
    // ֲ�ﱻ����ʱ�Ĵ���
    virtual void attacked(int damage)=0;

    // ����ֲ����ָ��λ��
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
    int health;   //����ֵ      
    int attackDamage;//�˺�ֵ
    int row;//��
    int col;//��
};

#endif // __PLANT_H__

