// PeaShooter.h
#ifndef __PEA_SHOOTER_H__
#define __PEA_SHOOTER_H__

#include "ShooterPlant.h"

class PeaShooter : public ShooterPlant {
public:
    PeaShooter();
    virtual ~PeaShooter();

    // ��ʼ������ֲ��
    virtual bool init();

    // ��д������Ϊ
    virtual void performAction() override;

    // ��ȡ����ֲ�������
    virtual std::string getType() override;

    CREATE_FUNC(PeaShooter);//����һ��PeaShooter����
};

#endif // __SHOOTER_PLANT_H__

