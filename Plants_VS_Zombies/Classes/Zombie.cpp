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

void Zombie::setStartTime(float time)
{
	startTime = time;
}

float Zombie::getStartTime()
{
	return startTime;
}

void Zombie::setCol(int Col)
{
	col = Col;
}

int Zombie::getCol()
{
	return col;
}

void Zombie::setCondition(int con)
{
	condition = con;
}

int Zombie::getCondition()
{
	return condition;
}