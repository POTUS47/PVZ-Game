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

private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;


};