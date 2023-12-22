#pragma once
//��Ϊ���в�ͬ���͵Ľ�ʬ��ĸ���
#include"cocos2d.h"
#include"Entity.h"

class Zombie :public Entity {
private:
	int HP;//��ʬѪ��
	int walkSpeed;//ǰ���ٶ�
	int col;//���������ǵڼ���
	float startTime;//����ʱ��
	bool lostHead = false;//��û�ж���ͷ������Ϊû��
	float eatPlantTime;//��ֲ���ʱ����
	float attackDegree;//������ֲ��۶���Ѫ
public:
	void setHP(int hp);//����Ѫ��
	int getHP();//��ȡѪ��

	void setSpeed(int speed);//����ǰ���ٶ�
	int getSpeed();//��ȡ��ʬ�����ٶ�

	void setStartTime(float time);//���ó���ʱ��
	float getStartTime();//��ȡ����ʱ��

	void setCol(int Col);//���ó�������
	int getCol();//��ȡ��������

	bool getHeadCondition();//��ȡͷ���ڲ���
	virtual void moveForward(Sprite* who) = 0;//��ǰ�ߵĶ���
	virtual void standBy(Sprite* who) = 0;//վ�ڵȴ����Ķ���
	virtual void healthyEating(Sprite* who) = 0;//û�б�������ֲ��Ķ���
	virtual void dieAndlay(Sprite* who) = 0;//�������ҵ��µĶ���
	virtual void loseHead(Sprite* who) = 0;//ͷ������
};