#pragma once
#include"cocos2d.h"
#define WAIT 0//�ڵȺ���
#define WALKING 1//����ǰ��
#define EATING 2//�ڳ�ֲ��


#define ENOUPH 9//��Ƭ���⹻���ܲ�����Ҫ�ж�
#define POOR 10//����ֵ��������
#define ABLE 11//��Ƭ���Ե��
#define SHOVEL 10

enum bulletCondition{NOT_USED,USED};//�ӵ�������״̬�������ӵ�����Ϊ����������������ʬ
enum plantName { SUNFLOWER=1,PEA_SHOOTER, NUT, DOUBLE_SHOOTER, SUN_FLOWER, SUN_SHROOM, PUFF_SHROOM,FUME_SHROOM,JALAPENO};//ֲ��������ǩ.
enum plantCondition{HEALTHY,DEAD,BEINGEATEN,SLEEP,BOMB};//bingeaten healthy dead���ڶԽӽ�ʬ��BOMB SLEEP����ֲ��������
USING_NS_CC;

class Entity {
private:
	Sprite* idv;
public:
	Sprite* getIdv();
	void setIdv(Sprite* _idv);
};