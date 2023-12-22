#pragma once
#include"cocos2d.h"
#include"Entity.h"

class Card :public Entity
{
public:
	//构造函数，传入位置，大小，图片路径
	Card(int x, int y, float scale, const std::string& imagePath,Scene*scene);
	//添加卡片监听器
};
