#include"Zombie.h"
USING_NS_CC;

void Zombie::setHP(int hp)
{
	HP = hp;//�����Զ���Ѫ��
}

int Zombie::getHP() {
	return HP;
}

void Zombie::setWeapen(bool wea)
{
	weapen = wea;
}

bool Zombie::getWeapen() 
{
	return weapen;
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

void Zombie::setEatingTime(float time)
{
	eatPlantTime = time;
}

float Zombie::getEatingTime()
{
	return eatPlantTime;
}

void Zombie::setAttack(int att)
{
	attackDegree = att;
}

int Zombie::getAttack()
{
	return attackDegree;
}

void Zombie::burning()
{
	getIdv()->stopAllActions();
	auto animation = Animation::create();
	char diearray[40] = { 0 };
	/*��ʬ�ճɻҽ�*/
	for (int i = 1; i < 21; i++)
	{
		sprintf(diearray, "/normalzombie/boomdust/%d.png", i);
		animation->addSpriteFrameWithFile(diearray);
	}
	animation->setDelayPerUnit(0.15f);
	animation->setLoops(1);//ֻ����һ��
	animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
	auto anim = Animate::create(animation);
	getIdv()->runAction(anim);
}