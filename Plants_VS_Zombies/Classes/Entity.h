#pragma once
#include"cocos2d.h"
#define WAIT 0//�ڵȺ���
#define WALKING 1//����ǰ��
#define EATING 2//�ڳ�ֲ��
#define DEAD 3//����

#define HEALTHY 4//������ֲ���ã�
#define BOMB 5//��������ը

enum plantName { PEA_SHOOTER, DOUBLE_SHOOTER, SUN_FLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//ֲ��������ǩ.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};