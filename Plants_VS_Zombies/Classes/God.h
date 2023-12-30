#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include"ConeHeadZombie.h"
#include"NewspaperZombie.h"
#include<iostream>
#include"Level.h"
//�����ֲ���ͷ�ļ�
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"
#include"Card.h"
#include"Car.h"
#include "peaBullet.h"
#include "puffShroomBullet.h"
#include"plant.h"
#include"flame.h"
#include "SunShroom.h"
#include"Jalapeno.h"
#include"PuffShroom.h"
#include"FumeShroom.h"



/*������������������Ϸ�Ƿ�����ȵ�*/
class God :public Node
{
private:
	int levelNum;
	int dayOrNight;//0�ǰ��죬1�Ǻ�ҹ
	Scene* currentScene;//GOD����ĵ�ǰ����ָ��
	Sun* sun;

public:
	//���캯��
	God(int isNight, Scene* currentScene, int LevelNum);
	void cleanup();
	//�����Ϸ�Ƿ����
	void gameEnd();
	//��⽩ʬ�Ƿ�����С�Ƴ�
	void hitByCar();
	//��Ϸ��ʼ�����ɽ�ʬ
	void updateZombies(int level);
	//���ݽ�ʬHP�жϽ�ʬ�Ƿ�����
	void dead();
	//����ʬ���ó���ʱ��
	void setZombieStartTime();
	//��������
	void createSun(cocos2d::Scene* scene);
	//������ٵ���ʾ
	void updateSun();
	//��ֲ��ѡ������չʾֲ�￨Ƭ
	void showCardinSeedBank(Scene* scene, Sun* _sun);
	//����С��
	void initCar(Scene* scene);
	//����Ƿ��н�ʬ��ֲ����ײ
	void checkCrush();
	//���ֲ���費��Ҫ�����ӵ�
	void checkAttack();
	//ɾ����vector�в���Ҫ���ӵ�
	void checkBulletToDelete();
	//��齩ʬҪ��Ҫ��ֲ��
	void checkEat();
	//��ֲ��
	bool plantPlant(Vec2 Point, int type);

	//����Ƿ�������Ҫ��ը
	void checkJalapenoBomb();
	//����Ƿ������⹽Ҫ����
	void sunShroomGrowUp();
	//���̫����������
	void checkSunflower();
	//���card��״̬
	void checkCard();
	//������
	void randomCardInit( Sun* _sun);


	void setSun(Sun* _sun) {
		sun = _sun;
	}

	void Win();//ʤ������
	void Lose();//ʧ�ܳ���
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void returnToMainMenu();

};