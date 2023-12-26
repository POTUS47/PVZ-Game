#pragma once
#include "Plant.h"

class Jalapeno : public Plant {
public:
    Jalapeno(int x, int y, double scale, Scene* scene);

    void onAnimationFinished(Node* sender);

    void working();
    void dieAnimation();
};