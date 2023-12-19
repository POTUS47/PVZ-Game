#pragma once
#include"Zombie.h"

class normalZombie :public Zombie {
private:
public:
	normalZombie(int x, int y, double scale, Scene* scene);
	virtual void moveForward(Sprite* who);
	virtual void standBy(Sprite* who);
	virtual void healthyEating(Sprite* who);
	virtual void dieAndlay(Sprite* who);
	virtual void loseHead(Sprite* who);
	void moveWithoutArm(Sprite* who);
};