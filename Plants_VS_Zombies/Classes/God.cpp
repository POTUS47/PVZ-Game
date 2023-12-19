#include"God.h"

/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
std::vector<Zombie*>dead;

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
	for (int i = 0; i < walking.size(); i++) {
		Sprite* current = walking[i]->getIdv();
		Vec2 pos= current->getPosition();
		if (pos.x <= 0) {
			exit(1);
			//调用gameover函数
		}
	}
}

void God::updateZombies(int level, Scene* scene)
{
	int normZ = 0;
	//根据关卡的不同设置不同数量的僵尸
	if (level == 1) {
		normZ = 5;
	}
	else {

	}

	//开始生成僵尸,放入等待容器中
	for (int i = 0; i < normZ; i++) {
		int x = rand() % 400 + 1300;
		int y = rand() % 800 + 1;
		waiting.push_back(new normalZombie(x, y, 2.0, scene));
	}
	for (int i = 0; i < normZ; i++) {
		waiting[i]->standBy(waiting[i]->getIdv());
	}
	waiting[2]->loseHead(waiting[2]->getIdv());
}

void God::dead()
{
	for (int i = 0; i < walking.size(); i++) {
		if (walking[i]->getHP() <= 0) {
			waiting[i]->dieAndlay(waiting[i]->getIdv());
		}
	}
}