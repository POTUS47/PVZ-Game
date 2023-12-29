#pragma once
#include "Plant.h"

class Nut : public Plant {
public:
    Nut(int x, int y, double scale, Scene* scene);

    void waitingAnimation();
    void dieAnimation();
};