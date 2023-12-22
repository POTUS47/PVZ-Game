#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include<iostream>
#include"Level1.h"
//�����ֲ���ͷ�ļ�
#include "PeaShooter.h"
#include "Nut.h"
#include "DoubleShooter.h"

/*������������������Ϸ�Ƿ�����ȵ�*/
class God :public Node
{
private:
	int dayOrNight;//0�ǰ��죬1�Ǻ�ҹ
	Label* sunLightLabel;//���Ͻ�����label
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
	Label* getSunLightLabel() { return sunLightLabel; }
	void changeSunLabel(Label* sunlabel) { sunLightLabel = sunlabel; }

};