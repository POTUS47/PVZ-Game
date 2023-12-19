#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include<iostream>



/*调度器放在这里，检测游戏是否结束等等*/
class God 
{
public:
	//检测游戏是否结束
	void gameEnd();
	//游戏开始，生成僵尸
	void updateZombies(int level,cocos2d::Scene* scene);
	//根据僵尸HP判断僵尸是否死亡
	void dead();
};