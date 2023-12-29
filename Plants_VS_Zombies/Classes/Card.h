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
	int type;//��¼�ÿ�Ƭ���ĸ�ֲ��
	int condition=POOR;//��Ƭ��״̬
	int money;//����ļ۸�
	int sleepTime;//����ʱ��

	int isNight;

public:
	//���캯��������λ�ã���С��ͼƬ·��,ֲ��ͼƬ·��
	Card(int x, int y, float scale, const std::string& imagePath, 
		const std::string& plantpath,Scene*_scene,int _type,Sun* _sun,int IsNight);
	//��ӿ�Ƭ������
	void addListener();
	void addMINIListener();
	//���ù���ֲ��ĺ���
	void createPlant(Vec2 real);
};
