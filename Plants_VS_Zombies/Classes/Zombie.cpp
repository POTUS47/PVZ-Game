//作为所有不同类型的僵尸类的父类
#include"cocos2d.h"
#include<iostream>
using namespace std;
class zombie :public cocos2d::Sprite {
public:
	static void test() {
		cocos2d::Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
		auto sample_zomnbie = Sprite::create("zombietest.png");
		sample_zomnbie->setPosition(500, 500);
		currentScene->addChild(sample_zomnbie,0);
	}
protected:
	Sprite* zombies;
};