#pragma once
#include "cocos2d.h"
/*调度器放在这里，检测游戏是否结束等等*/
class God 
{
public:
	//测试功能
	//每隔五秒在随机的一个地方产生一只僵尸
	void testt(float delta, cocos2d::Scene* scene);

	//检测游戏是否结束
	void gameEnd();
};