#pragma once
#include "cocos2d.h"

class Bullet : public cocos2d::Sprite {
public:
    Bullet();
    virtual ~Bullet();

    static Bullet* create(const std::string& bulletImage);

    void shootBullet(cocos2d::Vec2 startPosition, float speed);

private:
    void update(float dt);

    float bulletSpeed;
};