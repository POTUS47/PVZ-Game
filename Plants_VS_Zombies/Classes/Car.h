#pragma once
//小推车
#include"cocos2d.h"
#include"Entity.h"

class Car :public Entity
{
public:
	//构造函数，传入行位置
	Car(int col, Scene* scene);
	//车跑的动作
	void carRun();
};