#include"God.h"
#include"NormalZombie.h"
#include<iostream>
#include<vector>

/*���ڵȴ��Ľ�ʬ*/
std::vector<Zombie*>waiting;
/*�����Ľ�ʬ*/
std::vector<Zombie*>walking;
/*���˵Ľ�ʬ*/
std::vector<Zombie*>dead;

void God::testt(float delta, cocos2d::Scene* scene)
{
	//srand(time(0));
	/*int x = rand() % 1500 + 1;
	int y = rand() % 1500 + 1;
	normalZombie* zombie = new normalZombie(x, y, 2.0, scene);
	zombie->moveForward(zombie->getIdv());*/
	for (int i = 0; i < 10; ++i) {
		int x = rand() % 1500 + 1;
		int y = rand() % 1500 + 1;
		waiting.push_back(new normalZombie(x, y, 2.0, scene));
	}
	waiting[3]->loseHead(waiting[3]->getIdv());
}

//������ÿ��0.1����øú���
void God::gameEnd()
{
	for (int i = 0; i < walking.size(); i++) {
		//���ʬ��x����
	}
}