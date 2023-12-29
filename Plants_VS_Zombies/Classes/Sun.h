#pragma once
#include"cocos2d.h"
#include"Entity.h"

class Sun :public Entity
{
private:
	Label* sunLightLabel;//���Ͻ�����label
	Scene* currentScene;
	int sunValue;//����ֵ
	int sunNumber = 0;
	int littleSunNumber = 0;//ȫ�ֱ�������¼�����⣨25����С���⣨15���ĸ�����������������ǩ
public:
	Sun(Scene* scene);//���캯�������������ǩ
	void updateSun();//��������ֵ��ǩ
	void createSun();//�����������
	void flowerSun(Vec2 position,int kind);
	int getSunValue() {
		return sunValue;
	}
	void setSunValue(int value) {
		sunValue = value;
	}
};