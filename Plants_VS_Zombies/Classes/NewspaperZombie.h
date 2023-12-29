#pragma once
#include"Zombie.h"
#include"cocos2d.h"

class newspaperZombie :public Zombie {
private:
public:
	newspaperZombie(int x, int y, double scale, Scene* scene);
	virtual void moveForward(Sprite* who);

	virtual void standBy(Sprite* who);
	virtual void healthyEating(Sprite* who);
	virtual void dieAndlay(Sprite* who);
	virtual void loseHead(Sprite* who);
	void moveWithoutArm(Sprite* who);
};