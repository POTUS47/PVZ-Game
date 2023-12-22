#pragma once
#include "ShooterPlant.h"

class PeaShooter : public ShooterPlant {
public:
    PeaShooter(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
    void attackAnimation();
    void dieAnimation();
};


