#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
<<<<<<< Updated upstream
=======
#include"ConeHeadZombie.h"
#include"NewspaperZombie.h"
>>>>>>> Stashed changes
#include<iostream>
#include"Level1.h"
//�����ֲ���ͷ�ļ�
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"
<<<<<<< Updated upstream
=======
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
>>>>>>> Stashed changes

/*������������������Ϸ�Ƿ�����ȵ�*/
class God :public Node
{
private:
	int dayOrNight;//0�ǰ��죬1�Ǻ�ҹ
<<<<<<< Updated upstream
	Label* sunLightLabel;//���Ͻ�����label
=======
	Scene* currentScene;//GOD����ĵ�ǰ����ָ��
	Sun* sun;
>>>>>>> Stashed changes
public:
	//���캯��
	God(int isNight);
	//�����Ϸ�Ƿ����
	void gameEnd();
	//��Ϸ��ʼ�����ɽ�ʬ
	void updateZombies(int level,cocos2d::Scene* scene);
	//���ݽ�ʬHP�жϽ�ʬ�Ƿ�����
	void dead();
	//����ʬ���ó���ʱ��
	void setZombieStartTime();
	//��������
	void createSun(cocos2d::Scene* scene);
	//������ٵ���ʾ
	void updateSun();
<<<<<<< Updated upstream
	Label* getSunLightLabel() { return sunLightLabel; }
	void changeSunLabel(Label* sunlabel) { sunLightLabel = sunlabel; }
=======
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
	
	void setSun(Sun* _sun) {
		sun = _sun;
	}
>>>>>>> Stashed changes

};