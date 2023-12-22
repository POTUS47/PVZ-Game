#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet() : bulletSpeed(0.0f) {
}

Bullet::~Bullet() {
}

Bullet* Bullet::create(const std::string& bulletImage) {
    Bullet* bullet = new (std::nothrow) Bullet();
    if (bullet && bullet->initWithFile(bulletImage)) {
        bullet->autorelease();
        return bullet;
    }
    else {
        delete bullet;
        return nullptr;
    }
}

void Bullet::shootBullet(Vec2 startPosition, float speed) {
    this->setPosition(startPosition);
    this->bulletSpeed = speed;

    this->schedule(CC_SCHEDULE_SELECTOR(Bullet::update));
}

void Bullet::update(float dt) {
    Vec2 currentPosition = this->getPosition();
    currentPosition.x += bulletSpeed * dt;
    this->setPosition(currentPosition);

    // TODO: ��ײ����߼�������Ƿ���н�ʬ��

    // TODO: ������Ҫ��������߼������糬����Ļ�������ӵ�
}