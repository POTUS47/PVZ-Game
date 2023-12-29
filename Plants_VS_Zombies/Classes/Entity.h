#pragma once
#include"cocos2d.h"
#define WAIT 0//在等候区
#define WALKING 1//在向前走
#define EATING 2//在吃植物


#define ENOUPH 9//卡片阳光够但能不能买还要判断
#define POOR 10//阳光值不够购买
#define ABLE 11//卡片可以点击
#define SHOVEL 10

enum bulletCondition{NOT_USED,USED};//子弹的两种状态，避免子弹重因为动画滞留复攻击僵尸
enum plantName { SUNFLOWER=1,PEA_SHOOTER, NUT, DOUBLE_SHOOTER, SUN_FLOWER, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//植物姓名标签.
enum plantCondition{HEALTHY,DEAD,BEINGEATEN,SLEEP,BOMB};//bingeaten healthy dead用于对接僵尸，BOMB SLEEP用于植物自身工作
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};