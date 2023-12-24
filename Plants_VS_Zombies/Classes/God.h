#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include"ConeHeadZombie.h"
#include<iostream>
#include"Level1.h"
//添加了植物的头文件
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"
#include"Card.h"
#include"Car.h"
#include "Bullet.h"
#include"plant.h"


/*调度器放在这里，检测游戏是否结束等等*/
class God :public Node
{
private:
	int dayOrNight;//0是白天，1是黑夜
	Label* sunLightLabel;//左上角阳光label
	Scene* currentScene;//GOD管理的当前场景指针
public:
	//构造函数
	God(int isNight, Scene* currentScene);
	//检测游戏是否结束
	void gameEnd();
	//检测僵尸是否碰到小推车
	void hitByCar();
	//游戏开始，生成僵尸
	void updateZombies(int level);
	//根据僵尸HP判断僵尸是否死亡
	void dead();
	//给僵尸设置出发时间
	void setZombieStartTime();
	//生成阳光
	void createSun(cocos2d::Scene* scene);
	//阳光多少的显示
	void updateSun();
	//在植物选择器里展示植物卡片
	void showCardinSeedBank(Scene* scene);
	//生成小车
	void initCar(Scene* scene);
	//检测是否有僵尸和植物相撞
	void checkCrush();
	//检查植物需不需要发射子弹
	void checkAttack();
	//删除在vector中不需要的子弹
	void checkBulletToDelete();
	//检查僵尸要不要吃植物
	void checkEat();
	//种植物
	bool plantPlant(Vec2 Point, int type);
	
	Label* getSunLightLabel() { return sunLightLabel; }
	void changeSunLabel(Label* sunlabel) { sunLightLabel = sunlabel; }

};