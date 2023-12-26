#pragma once
#include "Plant.h"

class PuffShroom : public Plant {
public:
    PuffShroom(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
    void attackAnimation();
    void dieAnimation();
};