#pragma once

#include "Plant.h"

class DoubleShooter : public Plant {
public:
    DoubleShooter(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
};
