#pragma once
#include "cocos2d.h"
#include "Bullet.h"
class puffShroomBullet : public Bullet {
public:
    puffShroomBullet(int row, int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
};