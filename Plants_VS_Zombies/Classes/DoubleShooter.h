#pragma once

#include "ShooterPlant.h"

class DoubleShooter : public ShooterPlant {
public:
    DoubleShooter(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
    void attackAnimation();
    void dieAnimation();
};
