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
#define SUNFLOWER 1
#define PEASHOOTER 2
#define NUT 3
#define DOUBLESHOOTER 4
#define SUN_SHROOM 5
#define PUFF_SHROOM 6
#define FUME_SHROOM 7
#define JALAPENO 8



class Card :public Entity
{
private:
	Sun* sun;
	std::string plantPath;
	bool canClick;
	bool isFollowingMouse = false;
	Sprite* plantFollowSprite;
	Scene* scene;
	int type;//��¼�ÿ�Ƭ���ĸ�ֲ��
	int condition=POOR;//��Ƭ��״̬
	int money;//����ļ۸�
	int sleepTime;//����ʱ��
public:
	//���캯��������λ�ã���С��ͼƬ·��,ֲ��ͼƬ·��
	Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*_scene,int _type,Sun* _sun);
	//��ӿ�Ƭ������
	void addListener();
	//���ù���ֲ��ĺ���
	void createPlant(Vec2 real);
	void setCondition(int con) { condition = con; }
	int getCondition() { return condition; }
	void setMoney(int _money) { money = _money; }
	int getMoney() { return money; }
	void setSun(Sun* _sun) {
		sun = _sun;
	}
};

Vec2 checkPosition(Vec2 Point);
