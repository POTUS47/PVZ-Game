#pragma once
#include"cocos2d.h"
#define WAIT 0//�ڵȺ���
#define WALKING 1//����ǰ��
#define EATING 2//�ڳ�ֲ��
#define DEAD 3//����

#define HEALTHY 4//������ֲ���ã�
#define BEINGEATEN 5//���ԣ�ֲ���ã�
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};