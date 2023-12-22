//射手类植物
#ifndef __SHOOTER_PLANT_H__
#define __SHOOTER_PLANT_H__

#include "Plant.h"

class ShooterPlant : public Plant {
public:
    // 射手植物特有的射击函数
   void shoot();
};

#endif // __SHOOTER_PLANT_H__

