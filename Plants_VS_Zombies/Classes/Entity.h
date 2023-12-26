#pragma once
#include"cocos2d.h"
#define WAIT 0//在等候区
#define WALKING 1//在向前走
#define EATING 2//在吃植物
#define DEAD 3//死了

#define HEALTHY 4//健康（植物用）
#define BOMB 5//火爆辣椒爆炸

enum plantName { PEA_SHOOTER, DOUBLE_SHOOTER, SUN_FLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//植物姓名标签.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};