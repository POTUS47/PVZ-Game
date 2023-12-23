#pragma once
#include"cocos2d.h"
#include"Entity.h"
#include<string>

class Card :public Entity
{
private:
	bool isPressed;
	std::string plantPath;
	Sprite* exaplant = nullptr;
public:
	//构造函数，传入位置，大小，图片路径,植物图片路径
	Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*scene);
	//添加卡片监听器
};
