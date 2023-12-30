#pragma once
#include "Plant.h"

class PuffShroom : public Plant {
public:
    PuffShroom(int x, int y, double scale, Scene* scene, int isNight);

    void waitingAnimation();
    void attackAnimation();
};