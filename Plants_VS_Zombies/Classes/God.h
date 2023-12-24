#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include"ConeHeadZombie.h"
#include<iostream>
#include"Level1.h"
//�����ֲ���ͷ�ļ�
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"
#include"Card.h"
#include"Car.h"
#include "Bullet.h"
#include"plant.h"


/*������������������Ϸ�Ƿ�����ȵ�*/
class God :public Node
{
private:
	int dayOrNight;//0�ǰ��죬1�Ǻ�ҹ
	Label* sunLightLabel;//���Ͻ�����label
	Scene* currentScene;//GOD����ĵ�ǰ����ָ��
public:
	//���캯��
	God(int isNight, Scene* currentScene);
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
	void showCardinSeedBank(Scene* scene);
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
	
	Label* getSunLightLabel() { return sunLightLabel; }
	void changeSunLabel(Label* sunlabel) { sunLightLabel = sunlabel; }

};