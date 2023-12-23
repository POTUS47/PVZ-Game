#pragma once
//小推车
#include"cocos2d.h"
#include"Entity.h"

#define USED 0//车已经启动过了
#define NOTUSED 1//车没被启动过

class Car :public Entity
{
private:
	int condition;//车的状态
	int row;//车在第几行（1，2，3，4，5）
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
	//构造函数，传入行位置
	Car(int col, Scene* scene);
	//车跑的动作
	void carRun();
};