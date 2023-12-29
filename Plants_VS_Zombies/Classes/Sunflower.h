#pragma once

#include "Plant.h"

class Sunflower : public Plant{
public:
    Sunflower(int x, int y, double scale, Scene* scene,int isNight, Label* sunLightLabel);
    void waitingAnimation();
    void attackAnimation();
    void dieAnimation();

    void createSun(float dt);

    Scene* getScene() { return theScencePlantIn; }
    Label* getCurrentLevelSunLabel() {return currentLevelSunLabel;}
private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;
};