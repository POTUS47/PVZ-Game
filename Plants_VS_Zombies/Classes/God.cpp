#include"God.h"
#include"NormalZombie.h"
#include<iostream>
#include<vector>

/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
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

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
	for (int i = 0; i < walking.size(); i++) {
		//检查活僵尸的x坐标
	}
}