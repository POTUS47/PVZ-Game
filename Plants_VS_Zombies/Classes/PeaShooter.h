#pragma once
#include "Plant.h"

class PeaShooter : public Plant {
public:
    PeaShooter(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
    void dieAnimation();
};


