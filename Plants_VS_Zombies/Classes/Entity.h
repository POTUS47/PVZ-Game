#pragma once
#include"cocos2d.h"
#define WAIT 0//�ڵȺ���
#define WALKING 1//����ǰ��
#define EATING 2//�ڳ�ֲ��
#define DEAD 3//����

#define HEALTHY 4//������ֲ���ã�
#define BOMB 5//��������ը
#define PLANT_SLEEP 6//ֲ��˯��

#define SLEEP 6//��Ƭ����״̬
#define ENOUPH 7//��Ƭ���⹻���ܲ�����Ҫ�ж�
#define POOR 8//����ֵ��������
#define ABLE 9//��Ƭ���Ե��

#define SUNFLOWER 1
#define PEASHOOTER 2
#define NUT 3
#define DOUBLESHOOTER 4
#define SUN_SHROOM 5
#define PUFF_SHROOM 6
#define FUME_SHROOM 7
#define JALAPENO 8
//enum plantName { PEA_SHOOTER, DOUBLE_SHOOTER, SUN_FLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//ֲ��������ǩ.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};