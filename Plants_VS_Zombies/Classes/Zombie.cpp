//作为所有不同类型的僵尸类的父类
#include"cocos2d.h"
#include"Zombie.h"
USING_NS_CC;

void Zombie::setHP(int hp)
{
	HP = hp;//传入自定义血量
}

int Zombie::getHP() {
	return HP;
}

void Zombie::setSpeed(int speed)
{
	walkSpeed = speed;//传入自定义速度
}

int Zombie::getSpeed()
{
	return walkSpeed;
}

bool Zombie::getHeadCondition()
{
	return lostHead;
}