// PeaShooter.h
#ifndef __PEA_SHOOTER_H__
#define __PEA_SHOOTER_H__

#include "ShooterPlant.h"

class PeaShooter : public ShooterPlant {
public:
    PeaShooter();
    virtual ~PeaShooter();

    // 初始化射手植物
    virtual bool init();

    // 重写攻击行为
    virtual void performAction() override;

    // 获取射手植物的类型
    virtual std::string getType() override;

    CREATE_FUNC(PeaShooter);//创建一个PeaShooter对象
};

#endif // __SHOOTER_PLANT_H__

