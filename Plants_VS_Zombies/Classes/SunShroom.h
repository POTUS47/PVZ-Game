#pragma once

#include "Plant.h"
class SunShroom : public Plant {
public:
    SunShroom(int x, int y, double scale, Scene* scene, int isNight, Label* sunLightLabel);
    void waitingAnimation();
    void littleAnimation();
    void bigAnimation();
    void dieAnimation();

    void createSun(float dt);

    Scene* getScene() { return theScencePlantIn; }
    Label* getCurrentLevelSunLabel() { return currentLevelSunLabel; }
private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;
};