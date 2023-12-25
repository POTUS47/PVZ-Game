#pragma once
#include"cocos2d.h"
#define WAIT 0//在等候区
#define WALKING 1//在向前走
#define EATING 2//在吃植物
#define DEAD 3//死了

#define HEALTHY 4//健康（植物用）
#define BEINGEATEN 5//被吃（植物用）
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};