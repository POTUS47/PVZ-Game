#pragma once
//С�Ƴ�
#include"cocos2d.h"
#include"Entity.h"

class Car :public Entity
{
public:
	//���캯����������λ��
	Car(int col, Scene* scene);
	//���ܵĶ���
	void carRun();
};