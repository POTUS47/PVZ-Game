#pragma once
#include "Plant.h"

class FumeShroom : public Plant {
public:
    FumeShroom(int x, int y, double scale, Scene* scene,int isNight);

    void waitingAnimation();
    void dieAnimation();
    void attackAnimation();
};