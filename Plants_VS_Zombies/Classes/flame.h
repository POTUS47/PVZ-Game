#pragma once
#include "cocos2d.h"
#include "Bullet.h"
class Flame: public Bullet {
public:
    Flame(int row, int startX, int startY, int bulletDamage, Scene* scene);
};