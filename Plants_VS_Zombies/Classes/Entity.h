#pragma once
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#define WAIT 0//�ڵȺ���
#define WALKING 1//����ǰ��
#define EATING 2//�ڳ�ֲ��
#define DEAD 3//����

#define HEALTHY 4//������ֲ���ã�
#define BOMB 5//��������ը

#define SLEEP 8//��Ƭ����״̬
#define ENOUPH 9//��Ƭ���⹻���ܲ�����Ҫ�ж�
#define POOR 10//����ֵ��������
#define ABLE 11//��Ƭ���Ե��

#define MINIGAME 10
enum dayOrNight{DAY,NIGHT};
enum eatCon{BEINGEATEN,NOT_EATEN};
enum plantName{PEASHOOTER, DOUBLESHOOTER, SUNFLOWER, NUT, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO, SHOVEL};//ֲ��������ǩ.
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};