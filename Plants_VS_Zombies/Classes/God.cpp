#include"God.h"

/*���ڵȴ��Ľ�ʬ*/
std::vector<Zombie*>waiting;
/*�����Ľ�ʬ*/
std::vector<Zombie*>walking;
/*���˵Ľ�ʬ*/
std::vector<Zombie*>dead;

//������ÿ��0.1����øú���
void God::gameEnd()
{
	for (int i = 0; i < walking.size(); i++) {
		Sprite* current = walking[i]->getIdv();
		Vec2 pos= current->getPosition();
		if (pos.x <= 0) {
			exit(1);
			//����gameover����
		}
	}
}

void God::updateZombies(int level, Scene* scene)
{
	int normZ = 0;
	//���ݹؿ��Ĳ�ͬ���ò�ͬ�����Ľ�ʬ
	if (level == 1) {
		normZ = 5;
	}
	else {

	}

	//��ʼ���ɽ�ʬ,����ȴ�������
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