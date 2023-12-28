#pragma once
#include"cocos2d.h"
#include"Entity.h"

class Sun :public Entity
{
private:
	Label* sunLightLabel;//左上角阳光label
	Scene* currentScene;
	int sunValue;//阳光值
	int sunNumber = 0;
	int littleSunNumber = 0;//全局变量，记录大阳光（25）和小阳光（15）的个数，方便更新阳光标签
public:
	Sun(Scene* scene);//构造函数，建立阳光标签
	void updateSun();//更新阳光值标签
	void createSun();//生成随机阳光
	void flowerSun(Vec2 position,int kind);
	int getSunValue() {
		return sunValue;
	}
	void setSunValue(int value) {
		sunValue = value;
	}
};