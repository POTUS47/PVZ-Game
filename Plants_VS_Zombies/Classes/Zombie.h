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
	int attackDegree;//������ֲ��۶���Ѫ
	int condition;//��ʬ��״̬
	bool weapen;//��ʬ�Ƿ���������ñ�ӵ�
public:
	void setHP(int hp);//����Ѫ��
	int getHP()const;//��ȡѪ��

	void setWeapen(bool wea);//����Ѫ��
	bool getWeapen()const;//��ȡѪ��

	void setSpeed(int speed);//����ǰ���ٶ�
	int getSpeed()const;//��ȡ��ʬ�����ٶ�

	void setStartTime(float time);//���ó���ʱ��
	float getStartTime()const;//��ȡ����ʱ��

	void setCol(int Col);//���ó�������
	int getCol()const;//��ȡ��������

	void setCondition(int con);//���ý�ʬ״̬
	int getCondition()const;//��ȡ��ʬ״̬

	void setEatingTime(float time);//���ý�ʬ��ֲ���ʱ����
	float getEatingTime()const;//��ȡ��ʬ��ֲ���ʱ����

	void setAttack(int att);//���ý�ʬ��ֲ����˺�ֵ
	int getAttack()const;//��ȡ��ʬ��ֲ����˺�ֵ

	bool getHeadCondition();//��ȡͷ���ڲ���
	virtual void moveForward(Sprite* who) = 0;//��ǰ�ߵĶ���
	virtual void standBy(Sprite* who) = 0;//վ�ڵȴ����Ķ���
	virtual void healthyEating(Sprite* who) = 0;//û�б�������ֲ��Ķ���
	virtual void dieAndlay(Sprite* who) = 0;//�������ҵ��µĶ���
	virtual void loseHead(Sprite* who) = 0;//ͷ������
	void burning() ;//�ճɻҽ�
};