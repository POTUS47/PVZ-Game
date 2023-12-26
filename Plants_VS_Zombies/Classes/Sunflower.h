#pragma once
#include"Sun.h"
#include "Plant.h"

class Sunflower : public Plant{
public:
    Sunflower(int x, int y, double scale, Scene* scene,int isNight);
    void waitingAnimation();
    void attackAnimation();
    void dieAnimation();

    void createSun(int x,int y);

    Scene* getScene() { return theScencePlantIn; }
    Label* getCurrentLevelSunLabel() {return currentLevelSunLabel;}

   
private:
    Scene* theScencePlantIn;
    Label* currentLevelSunLabel;
    
};