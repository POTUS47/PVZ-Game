#pragma once
#include"cocos2d.h"
#include"Entity.h"
#include"plant.h"
#include"PeaShooter.h"
#include "PeaShooter.h"
#include"Sunflower.h"
#include "Nut.h"
#include "DoubleShooter.h"
#include"Card.h"
#include"Car.h"
#include "peaBullet.h"
#include "puffShroomBullet.h"
#include"plant.h"
#include"flame.h"
#include"Jalapeno.h"
#include"PuffShroom.h"
#include"FumeShroom.h"
#include"God.h"
#include"Sun.h"
#include<vector>
#include<string>




class Card :public Entity
{
private:
	Sun* sun;
	std::string plantPath;//植物的路径
	std::string cardPath;//卡片的路径
	std::string waitCardPath;//冷却卡片的路径
	bool canClick;
	bool isFollowingMouse = false;
	Sprite* plantFollowSprite;
	Scene* scene;
	int type;//记录该卡片是哪个植物
	int condition=POOR;//卡片的状态
	int money;//购买的价格
	int sleepTime;//休眠时间
	int isNight;
public:
	//构造函数，传入位置，大小，图片路径,植物图片路径
	Card(int x, int y, float scale, const std::string& imagePath,
		const std::string& plantpath,Scene*_scene,int _type,Sun* _sun, int IsNight);
	//添加卡片监听器
	void addListener();
	void addMINIListener();
	//调用构造植物的函数
	void createPlant(Vec2 real);
	void setCondition(int con) { condition = con; }
	int getCondition() { return condition; }
	void setMoney(int _money) { money = _money; }
	int getMoney() { return money; }
	void changeApperence(int kind);
	void setSun(Sun* _sun) {
		sun = _sun;
	}
};

Vec2 checkPosition(Vec2 Point);
