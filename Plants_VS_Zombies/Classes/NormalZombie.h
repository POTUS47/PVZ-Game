#pragma once
#include"Zombie.h"

class normalZombie :public Zombie {
private:
public:
	virtual Sprite* generateOne(Scene* scene);
	virtual void moveForward(Sprite* who);
	void moveWithoutArm(Sprite* who);
	void die(Sprite* who);
	void healthyAttack(Sprite* who);
	void loseHead(Sprite* who);
};