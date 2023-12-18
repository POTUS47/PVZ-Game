#pragma once
#include"Entity.h"

class Zombie :public Entity {
private:
	int HP;//僵尸血量
	int walkSpeed=20;//前进速度
	struct initialPosition {
		float row;
		float col;
	};
	bool lostHead = false;//有没有丢掉头，初设为没有
	float eatPlantTime;//吃植物的时间间隔
	float attackDegree;//攻击给植物扣多少血
public:
	void setHP(int hp);//设置血量
	int getHP();//获取血量
	void setSpeed(int speed);//设置前进速度
	int getSpeed();//获取僵尸行走速度
	bool getHeadCondition();//获取头还在不在
	virtual Sprite* generateOne(Scene* scene) = 0;//在特定的位置以特定的图片生成僵尸
	virtual void moveForward(Sprite* who) = 0;//向前走的动作
	virtual void standBy(Sprite* who) = 0;//站在等待区的动作
};