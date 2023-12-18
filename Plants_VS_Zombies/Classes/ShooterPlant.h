//������ֲ��
#ifndef __SHOOTER_PLANT_H__
#define __SHOOTER_PLANT_H__

#include "Plant.h"

class ShooterPlant : public Plant {
public:
    ShooterPlant();
    virtual ~ShooterPlant();

    // ��ʼ������ֲ��
    virtual bool init() override;

    // ��д������Ϊ
    virtual void performAction() override;

    // ��ȡ����ֲ�������
    virtual std::string getType() override;

    // ����ֲ�����е��������
    void shoot();

    CREATE_FUNC(ShooterPlant);
};

#endif // __SHOOTER_PLANT_H__

