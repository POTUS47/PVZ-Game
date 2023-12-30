#pragma once
#include"Sun.h"
#include"Entity.h"
#include "Plant.h"

class Sunflower : public Plant{
public:
    Sunflower(int x, int y, double scale, Scene* scene,int isNight);
    void waitingAnimation();
    void attackAnimation();

    Scene* getScene() { return theScencePlantIn; }
private:
    Scene* theScencePlantIn;
    
};