#pragma once
#include "cocos2d.h"
#include<vector>
#include"NormalZombie.h"
#include<iostream>



/*������������������Ϸ�Ƿ�����ȵ�*/
class God 
{
public:
	//�����Ϸ�Ƿ����
	void gameEnd();
	//��Ϸ��ʼ�����ɽ�ʬ
	void updateZombies(int level,cocos2d::Scene* scene);
	//���ݽ�ʬHP�жϽ�ʬ�Ƿ�����
	void dead();
};