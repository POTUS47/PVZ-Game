#pragma once
#include"Entity.h"

class Zombie :public Entity {
private:
	int HP;//��ʬѪ��
	int walkSpeed=20;//ǰ���ٶ�
	struct initialPosition {
		float row;
		float col;
	};
	bool lostHead = false;//��û�ж���ͷ������Ϊû��
	float eatPlantTime;//��ֲ���ʱ����
	float attackDegree;//������ֲ��۶���Ѫ
public:
	void setHP(int hp);//����Ѫ��
	int getHP();//��ȡѪ��
	void setSpeed(int speed);//����ǰ���ٶ�
	int getSpeed();//��ȡ��ʬ�����ٶ�
	bool getHeadCondition();//��ȡͷ���ڲ���
	virtual Sprite* generateOne(Scene* scene) = 0;//���ض���λ�����ض���ͼƬ���ɽ�ʬ
	virtual void moveForward(Sprite* who) = 0;//��ǰ�ߵĶ���
	virtual void standBy(Sprite* who) = 0;//վ�ڵȴ����Ķ���
};