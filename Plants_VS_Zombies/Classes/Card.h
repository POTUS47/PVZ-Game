#pragma once
#include"cocos2d.h"
#include"Entity.h"
#include<string>
#define SUNFLOWER 1
#define PEASHOOTER 2
#define NUT 3
#define DOUBLESHOOTER 4



class Card :public Entity
{
public:
	std::string plantPath;
	bool canClick;
	bool isFollowingMouse = false;
	Sprite* plantFollowSprite;
	Scene* scene;
	int type;//记录该卡片是哪个植物
public:
	//构造函数，传入位置，大小，图片路径,植物图片路径
	Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*_scene,int _type);
	//添加卡片监听器
	void addListener();
	//调用构造植物的函数
	void createPlant(Vec2 real);
};
