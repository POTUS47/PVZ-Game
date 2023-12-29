#pragma once

#include "Plant.h"
class SunShroom : public Plant {
public:
    SunShroom(int x, int y, double scale, Scene* scene, int isNight);

    void waitingAnimation();
    void littleAnimation();
    void bigAnimation();
    void dieAnimation();

    Scene* getScene() { return theScencePlantIn; }
    Label* getCurrentLevelSunLabel() { return currentLevelSunLabel; }

    void growUp();
    bool isBig = false;//标记是否长大，初设为否

private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;


};