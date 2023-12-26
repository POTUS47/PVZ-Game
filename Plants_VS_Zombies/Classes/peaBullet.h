#pragma once
#include "cocos2d.h"
#include "Bullet.h"
class peaBullet : public Bullet{
public:
    peaBullet(int row,int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
};