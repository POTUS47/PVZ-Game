//��Ϊ���в�ͬ���͵Ľ�ʬ��ĸ���
#include"cocos2d.h"
#include"Zombie.h"
USING_NS_CC;

void Zombie::setHP(int hp)
{
	HP = hp;//�����Զ���Ѫ��
}

int Zombie::getHP() {
	return HP;
}

void Zombie::setSpeed(int speed)
{
	walkSpeed = speed;//�����Զ����ٶ�
}

int Zombie::getSpeed()
{
	return walkSpeed;
}

bool Zombie::getHeadCondition()
{
	return lostHead;
}