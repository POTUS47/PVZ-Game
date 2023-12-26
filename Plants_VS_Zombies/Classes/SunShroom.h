#pragma once

#include "Plant.h"
class SunShroom : public Plant {
public:
    SunShroom(int x, int y, double scale, Scene* scene, int isNight, Label* sunLightLabel);
    void waitingAnimation();
    void littleAnimation();
    void bigAnimation();
    void dieAnimation();

    Scene* getScene() { return theScencePlantIn; }
    Label* getCurrentLevelSunLabel() { return currentLevelSunLabel; }
    long long int getPlantTime() { return plantTime; }//获取植物种植时间

    void  createLittleSun(float dt);
    void  createSun(float dt);

private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;
    long long int plantTime;
};