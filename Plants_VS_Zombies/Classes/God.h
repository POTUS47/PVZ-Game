#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include<iostream>
#include"Level1.h"
//添加了植物的头文件
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"

/*调度器放在这里，检测游戏是否结束等等*/
class God :public Node
{
private:
	int dayOrNight;//0是白天，1是黑夜
	Label* sunLightLabel;//左上角阳光label
public:
	//构造函数
	God(int isNight);
	//检测游戏是否结束
	void gameEnd();
	//游戏开始，生成僵尸
	void updateZombies(int level,cocos2d::Scene* scene);
	//根据僵尸HP判断僵尸是否死亡
	void dead();
	//给僵尸设置出发时间
	void setZombieStartTime();
	//生成阳光
	void createSun(cocos2d::Scene* scene);
	//阳光多少的显示
	void updateSun();
	Label* getSunLightLabel() { return sunLightLabel; }
	void changeSunLabel(Label* sunlabel) { sunLightLabel = sunlabel; }

};