#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include<iostream>
#include"Level1.h"



/*������������������Ϸ�Ƿ�����ȵ�*/
class God :public Node
{
private:
	
public:
	//���캯��
	God();
	//�����Ϸ�Ƿ����
	void gameEnd();
	//��Ϸ��ʼ�����ɽ�ʬ
	void updateZombies(int level,cocos2d::Scene* scene);
	//���ݽ�ʬHP�жϽ�ʬ�Ƿ�����
	void dead();
	//����ʬ���ó���ʱ��
	void setZombieStartTime();
	//��������
	void createSun(cocos2d::Scene* scene, Label* sunLightLabel);
	//������ٵ���ʾ
	void updateSun(Label* sunlightLabel);
};