#pragma once
//С�Ƴ�
#include"cocos2d.h"
#include"Entity.h"

#define USED 0//���Ѿ���������
#define NOTUSED 1//��û��������

class Car :public Entity
{
private:
	int condition;//����״̬
	int row;//���ڵڼ��У�1��2��3��4��5��
public:
	void setCondition(int con) {
		condition = con;
	}
	int getCondition() {
		return condition;
	}
	void setRow(int Row) {
		row = Row;
	}
	int getRow() {
		return row;
	}
	//���캯����������λ��
	Car(int col, Scene* scene);
	//���ܵĶ���
	void carRun();
};