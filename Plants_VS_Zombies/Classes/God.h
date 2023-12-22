#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include"ConeHeadZombie.h"
#include<iostream>
#include"Level1.h"
#include"Card.h"
#include"Car.h"



/*调度器放在这里，检测游戏是否结束等等*/
class God :public Node
{
private:
	
public:
	//构造函数
	God();
	//检测游戏是否结束
	void gameEnd();
	//检测僵尸是否碰到小推车
	void hitByCar();
	//游戏开始，生成僵尸
	void updateZombies(int level,cocos2d::Scene* scene);
	//根据僵尸HP判断僵尸是否死亡
	void dead();
	//给僵尸设置出发时间
	void setZombieStartTime();
	//生成阳光
	void createSun(cocos2d::Scene* scene, Label* sunLightLabel);
	//阳光多少的显示
	void updateSun(Label* sunlightLabel);
	//在植物选择器里展示植物卡片
	void showCardinSeedBank(Scene*scene);
	//生成小车
	void initCar(Scene* scene);
};