#pragma once
//作为所有不同类型的僵尸类的父类
#include"cocos2d.h"
#include"Entity.h"

class Zombie :public Entity {
private:
	int HP;//僵尸血量
	int walkSpeed;//前进速度
	int col;//出发赛道是第几行
	float startTime;//出发时间
	bool lostHead = false;//有没有丢掉头，初设为没有
	float eatPlantTime;//吃植物的时间间隔
	int attackDegree;//攻击给植物扣多少血
	int condition;//僵尸的状态
	bool weapen;//僵尸是否有武器？帽子等
public:
	void setHP(int hp);//设置血量
	int getHP()const;//获取血量

	void setWeapen(bool wea);//设置血量
	bool getWeapen()const;//获取血量

	void setSpeed(int speed);//设置前进速度
	int getSpeed()const;//获取僵尸行走速度

	void setStartTime(float time);//设置出发时间
	float getStartTime()const;//获取出发时间

	void setCol(int Col);//设置出发赛道
	int getCol()const;//获取出发赛道

	void setCondition(int con);//设置僵尸状态
	int getCondition()const;//获取僵尸状态

	void setEatingTime(float time);//设置僵尸吃植物的时间间隔
	float getEatingTime()const;//获取僵尸吃植物的时间间隔

	void setAttack(int att);//设置僵尸吃植物的伤害值
	int getAttack()const;//获取僵尸吃植物的伤害值

	bool getHeadCondition();//获取头还在不在
	virtual void moveForward(Sprite* who) = 0;//向前走的动作
	virtual void standBy(Sprite* who) = 0;//站在等待区的动作
	virtual void healthyEating(Sprite* who) = 0;//没有被攻击吃植物的动作
	virtual void dieAndlay(Sprite* who) = 0;//死亡并且倒下的动作
	virtual void loseHead(Sprite* who) = 0;//头掉动作
	void burning() ;//烧成灰烬
};