#pragma once
#include"cocos2d.h"
#define WAIT 0//在等候区
#define WALKING 1//在向前走
#define EATING 2//在吃植物
#define DEAD 3//死了

#define HEALTHY 4//健康（植物用）
#define BOMB 5//火爆辣椒爆炸
#define PLANT_SLEEP 6//植物睡觉
#define BEINGEATEN 7

#define SLEEP 8//卡片休眠状态
#define ENOUPH 9//卡片阳光够但能不能买还要判断
#define POOR 10//阳光值不够购买
#define ABLE 11//卡片可以点击

#define SUNFLOWER 1
#define PEASHOOTER 2
#define NUT 3
#define DOUBLESHOOTER 4
#define SUN_SHROOM 5
#define PUFF_SHROOM 6
#define FUME_SHROOM 7
#define JALAPENO 8

#define SHOVEL 9
//enum plantName { PEA_SHOOTER, DOUBLE_SHOOTER, SUN_FLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//植物姓名标签.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};