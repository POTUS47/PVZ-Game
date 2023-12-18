//射手类植物
#ifndef __SHOOTER_PLANT_H__
#define __SHOOTER_PLANT_H__

#include "Plant.h"

class ShooterPlant : public Plant {
public:
    ShooterPlant();
    virtual ~ShooterPlant();

    // 初始化射手植物
    virtual bool init() override;

    // 重写攻击行为
    virtual void performAction() override;

    // 获取射手植物的类型
    virtual std::string getType() override;

    // 射手植物特有的射击函数
    void shoot();

    CREATE_FUNC(ShooterPlant);
};

#endif // __SHOOTER_PLANT_H__

