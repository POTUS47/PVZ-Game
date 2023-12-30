#pragma once
#include "Level.h"
class MiniGameLevel :public Level {
public:
	void onMoveByFinished()override;
	void startChoose()override;
	void setBackground()override;
	static MiniGameLevel* createWithLevelNumber(int levelNumber);
	bool initWithLevelNumber(int levelNumber)override;// ³õÊ¼»¯º¯Êý
	void update(float dt);

};