#pragma once

#include "Plant.h"
class SunShroom : public Plant {
public:
    SunShroom(int x, int y, double scale, Scene* scene, int isNight);

    void waitingAnimation();
    void littleAnimation();
    void bigAnimation();

    Scene* getScene() { return theScencePlantIn; }

    void growUp();
    bool isBig = false;//����Ƿ񳤴󣬳���Ϊ��

private:
    Scene* theScencePlantIn;
};