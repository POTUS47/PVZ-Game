//ֲ����
#ifndef __PLANT_H__
#define __PLANT_H__

#include "cocos2d.h"

class Plant : public cocos2d::Sprite {
public:
    Plant();
    virtual ~Plant();

    // ֲ��Ļ�����Ϊ�����繥����ʬ
    virtual void performAction();

    // ֲ�ﱻ����ʱ�Ĵ���
    virtual void takeDamage(int damage);

    // ��ȡֲ�������
    virtual std::string getType();

    // ����ֲ����ָ��λ��
    void plantAtPosition(const cocos2d::Vec2& position, const cocos2d::Scene* a);

    // ��ȡֲ�������ֵ
    int getHealth() const { return health; }

    // ��ȡֲ��Ĺ���ֵ
    int getAttackDamage() const { return attackDamage; }

    // ��ȡֲ���λ��
    cocos2d::Vec2 GetPosition() const { return this->getPosition(); }


    int health;         
    int attackDamage;

};

#endif // __PLANT_H__

