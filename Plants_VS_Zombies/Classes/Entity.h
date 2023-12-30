#pragma once
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#define WAIT 0//在等候区
#define WALKING 1//在向前走
#define EATING 2//在吃植物
#define DEAD 3//死了

#define HEALTHY 4//健康（植物用）
#define BOMB 5//火爆辣椒爆炸

#define SLEEP 8//卡片休眠状态
#define ENOUPH 9//卡片阳光够但能不能买还要判断
#define POOR 10//阳光值不够购买
#define ABLE 11//卡片可以点击

#define MINIGAME 10
enum dayOrNight{DAY,NIGHT};
enum eatCon{BEINGEATEN,NOT_EATEN};
enum plantName{PEASHOOTER, DOUBLESHOOTER, SUNFLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO, SHOVEL};//植物姓名标签.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};