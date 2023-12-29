#pragma once
#include "cocos2d.h"
#include "Bullet.h"
class puffShroomBullet : public Bullet {
public:
    puffShroomBullet(int scale,int _row, int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
};