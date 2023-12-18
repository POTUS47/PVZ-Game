#pragma once
#include"Zombie.h"

class normalZombie :public Zombie {
private:
public:
	normalZombie(int x, int y, double scale, Scene* scene);
	virtual Sprite* generateOne(Scene* scene);
	virtual void moveForward(Sprite* who);
	void moveWithoutArm(Sprite* who);
	void die(Sprite* who);
	void healthyAttack(Sprite* who);
	void loseHead(Sprite* who);
};