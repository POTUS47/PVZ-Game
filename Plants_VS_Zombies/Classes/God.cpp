#include"God.h"
#include<algorithm>
std::vector<Card*>cards;
std::vector<Card*>randCards;//�����Ƭ������
/*С�Ƴ�*/
std::vector<Car*>littleCar;
/*���ڵȴ��Ľ�ʬ*/
std::vector<Zombie*>waiting;
/*�����Ľ�ʬ*/
std::vector<Zombie*>walking;
/*���˵Ľ�ʬ*/
std::vector<Zombie*>dead;


/*��ǰ�ؿ�������ֲ��*/
std::vector<Plant*>plants;

std::vector<Bullet*>bullets;//�ӵ�������
bool isIntersecting(Sprite* spriteA, Sprite* spriteB);//��������

/*���鴢�����ʱ��*/
float Statime[2][3][10] = { 15,25,40,45,67,80,89,88,90,105,45,50,75,78,90,35,70,75,87};//level type number


//God�Ĺ��캯��
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
}

//������ÿ��0.1����øú���
void God::gameEnd()
{
	int totaldeath = 0;
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() == DEAD) {
			totaldeath++;
			if (totaldeath == 18) {
				//Ӯ��
				exit(2);
			}
		}
		else {
			Vec2 currentPosition = waiting[i]->getIdv()->getPosition();
			if (currentPosition.x <= 0) {
				//����
				exit(1);
			}
		}	
	}
}

void God::updateZombies(int level)
{
	int normZ = 0;
	int coneZ = 0;
	int newsZ = 0;
	//���ݹؿ��Ĳ�ͬ���ò�ͬ�����Ľ�ʬ
	if (level == 1) {
		normZ = 10;
		coneZ = 5;
		newsZ = 3;
	}
	else {

	}



	//��ʼ���ɽ�ʬ,����ȴ�������
	//��ͨ��ʬ
	for (int i = 0; i < normZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new normalZombie(x, y, 2.0, currentScene));
	}
	//Բ׶��ʬ---
	for (int i = 0; i < coneZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new coneHeadZombie(x, y, 2.0, currentScene));
	}
	//��ֽ��ʬ---
	for (int i = 0; i < newsZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new newspaperZombie(x, y, 2.0, currentScene));
	}
	//�����еȴ����Ľ�ʬ����ȴ�״̬�������ó���ʱ�䣬���ó�������
	for (int i = 0; i < waiting.size(); i++) {
		int col = rand() % 5 + 1;
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);//���ó���ʱ��
		waiting[i]->setCol(col);//���ó�������
	}


	//��鷢�֣������ܹ�1920
/* ֲ���λ�� ������ֱ���160 350 540 730 920�ȽϺã��Ȳ�190��
* ������ֱ��� 215 405...���Ȳ�190��
* ֲ���row=(y-160)/190+1
*/
}

void God::dead()
{
	//����Ƿ��н�ʬ����
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() != DEAD) {//��ʬû���ټ��
			if (waiting[i]->getHP() <= 0) {
				waiting[i]->setCondition(DEAD);
				waiting[i]->dieAndlay(waiting[i]->getIdv());
				//���˵Ķ����������˾Ͱ�������˵Ľ�ʬ��vector��ɾ��
				auto delay = DelayTime::create(1.5f);
				auto sequence = Sequence::create(delay, CallFunc::create([=]() {
					waiting[i]->getIdv()->removeFromParent(); //��ʬ���˲��Ƴ�
					//waiting.erase(waiting.begin() + i);
					}), nullptr);
				waiting[i]->getIdv()->runAction(sequence);
			}
			else if (waiting[i]->getHP() <= 60) {
				if (waiting[i]->getWeapen() == true) {
					waiting[i]->setWeapen(false);
					if (waiting[i]->getCondition() == WALKING) {
						waiting[i]->moveForward(waiting[i]->getIdv());
					}
					else if (waiting[i]->getCondition() == EATING) {
						waiting[i]->healthyEating(waiting[i]->getIdv());
					}
				}
				
			}
		}
		
	}
}

void God::setZombieStartTime()
{
	int num = waiting.size();
	for (int i = 0; i < num; i++) {
		float delayT = waiting[i]->getStartTime();
		auto delay = DelayTime::create(delayT);
		
		auto delayedCallback = CallFunc::create([=]() {
			waiting[i]->moveForward(waiting[i]->getIdv()); // ���� moveForward ������ Sprite ����
			//waiting[i]->setCondition(WALKING);��Ϊ��moveforward��ʵ��
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

void God::showCardinSeedBank(Scene* scene,Sun* _sun)
{

	cards.push_back(new Card(268, 1108, 1.95, "/card/peashooter", "/plant/peashooter/Peashooter1.png", scene,PEASHOOTER,_sun, dayOrNight));
	cards.push_back(new Card(380, 1108, 1.95, "/card/sunflower", "/plant/sunflower/SunFlower1.png", scene, SUNFLOWER, _sun, dayOrNight));
	cards.push_back(new Card(492, 1108, 1.95, "/card/nut", "/plant/nut/zz1.png", scene,NUT,_sun, dayOrNight));
	cards.push_back(new Card(604, 1108, 1.95, "/card/repeatershooter", "/plant/doubleshooter/Repeater1.png", scene,DOUBLESHOOTER,_sun, dayOrNight));
	cards.push_back(new Card(716, 1108, 1.95, "/card/sunshroom", "/plant/sunshroom/b0.png",scene, SUN_SHROOM, _sun, dayOrNight));
	cards.push_back(new Card(828, 1108, 1.95, "/card/jalapeno", "/plant/jalapeno/j (1).png", scene, JALAPENO, _sun, dayOrNight));
	cards.push_back(new Card(940, 1108, 1.2, "/card/fumeshroom", "/plant/fumeshroom/s (1).png", scene, FUME_SHROOM, _sun, dayOrNight));
	cards.push_back(new Card(1052, 1108, 1.95, "/card/puffshroom", "/plant/puffshroom/w (1).png", scene, PUFF_SHROOM, _sun, dayOrNight));
	
	cards.push_back(new Card(1164, 1108, 1.05, "/card/shovel", "/card/shovel.png", scene, SHOVEL, _sun, dayOrNight));
}



void God::initCar(Scene* scene)
{
	for (int i = 1; i < 6; i++) {
		littleCar.push_back(new Car(i, scene));
	}
}

void God::hitByCar()
{
	for (int j = 0; j < waiting.size(); j++) {//����ÿһֻ��ʬ
		int zombieCon = waiting[j]->getCondition();
		if (zombieCon == WALKING || zombieCon == EATING) {//ֻ��������·�����ڳԵĽ�ʬ�ᱻײ
			for (int i = 0; i < littleCar.size(); i++) {//����ÿ����
				int zombieRow = waiting[j]->getCol();//��ȡ��ʬ����
				int carRow = littleCar[i]->getRow();//��ȡ�����ڵ���
				if (zombieRow == carRow&& isIntersecting(waiting[j]->getIdv(), littleCar[i]->getIdv())) {//ֻ����ͬһ�в��ж���Ҫ����
					if (littleCar[waiting[j]->getCol() - 1]->getCondition() == NOTUSED) {//�����û������
						littleCar[waiting[j]->getCol() - 1]->setCondition(USED);//���Ϊ������
						littleCar[waiting[j]->getCol() - 1]->carRun();
					}
					else {//�����������
						waiting[j]->setHP(-100);
					}
				}
			}
		}
	}
}

//��齩ʬ���ӵ���û����ײ
void God::checkCrush() {
	for (int i = 0; i < bullets.size(); i++) {//���������ӵ�
		for (int j = 0; j<waiting.size(); j++) {//�������н�ʬ
			if ((!bullets[i]->NeedRemove()) && (waiting[j]->getCondition() != DEAD)) {//����ӵ�����Ҫ���Ƴ��ľͲ����ж��Ƿ�Ӵ���ʬ
				if (isIntersecting(bullets[i]->getIdv(), waiting[j]->getIdv())) {//����ӵ����Ͻ�ʬ
					int bulletRow = bullets[i]->getRow();//��ȡ�ӵ����ڵڼ���
					int zombieRow = waiting[j]->getCol();//��ȡ��ʬ�ڵڼ���
					if (bulletRow == zombieRow) {
						bullets[i]->explodeAnimation();//�ӵ���ը��Ч��ͣ��0.4����ӵ������parent�Ƴ���Ȼ����ΪҪ��vectorɾ��
						if (bullets[i]->condition == 0) {
							int currentHP = waiting[j]->getHP();
							int minus = bullets[i]->getDamgeVlue();
							waiting[j]->setHP(currentHP -= minus);
							bullets[i]->condition = 1;//��֤һ���ӵ�ֻ��һ��Ѫ��������
						}

					}
				}
			}
			
		}
	}
}

void God::checkEat()
{
	for (int i = 0; i < plants.size(); i++) {
		for (int j = 0; j < waiting.size(); j++) {
			int zombieCon = waiting[j]->getCondition();
			int plantRow = plants[i]->getRow();//��ȡֲ�����ڵڼ���
			int zombieRow = waiting[j]->getCol();//��ȡ��ʬ�ڵڼ���

			if (zombieCon == WALKING) {//�����ʬ����·��;��
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//����ֲ������ͬһ��
					if (plants[i]-> getCondition()!=DEAD) {
						waiting[j]->setCondition(EATING);//��ʬ��Ϊ�ڳ�
						plants[i]->setEatCondition(BEINGEATEN);

						waiting[j]->healthyEating(waiting[j]->getIdv());
						//plants[i]->getHurt(waiting[j]->getAttack());///////////////////////////////////////////////////////������ֵ��Ҫ������
					}
				}
			}
			else if (zombieCon == EATING) {//��ʬ���ڳ���

				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//����ֲ������ͬһ��
					if (plants[i]->getCondition() == DEAD) {//ֲ������

						waiting[j]->moveForward(waiting[j]->getIdv());//��ʬ��Ϊ��·
					}
					else if (plants[i]->getEatCondition() == BEINGEATEN) {//ֲ���Ǳ���״̬Ҫ��Ѫ
						int attack = waiting[j]->getAttack();
						plants[i]->getHurt(attack);
						if (plants[i]->getCondition() == DEAD)
							continue;
						plants[i]->setEatCondition(NOT_EATEN);//һ��ֻ��һ�Σ�����Ѫ��ؽ���״̬
						auto delay = DelayTime::create(waiting[j]->getEatingTime());
						auto delayedCallback = CallFunc::create([=]() {
							plants[i]->setEatCondition(BEINGEATEN);//��һ��ʱ���Ϊ����
							});
						auto sequence = Sequence::create(delay, delayedCallback, nullptr);
						plants[i]->getIdv()->runAction(sequence);
					}
				}
			}
		}
	}

}

//���ڼ�����������������ĸ�������
bool isIntersecting(Sprite* spriteA, Sprite* spriteB) {
	Rect rectA = spriteA->getBoundingBox();
	Rect rectB = spriteB->getBoundingBox();

	return rectA.intersectsRect(rectB);
}

//���ֲ���費��Ҫ�����ӵ�,����2s���һ�Σ�
void God::checkAttack() {
	int isNight = dayOrNight;
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getAttackDamage() != 0&&plants[i]->getCondition()!=DEAD&& plants[i]->getCondition() != SLEEP) {//ɸ��������ֲ����ֲ�ﲻ������
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//�������н�ʬ
				if (waiting[j]->getCondition() == WALKING|| waiting[j]->getCondition() ==EATING) {//�õ����ŵĻ������ڳԵĽ�ʬ
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//��ֲ������������Ϊ
						Vec2 currentP=plants[i]->getIdv()->getPosition();//��ȡҪ�����ӵ���ֲ���λ��
						if(plants[i]->getName()==PEASHOOTER)
						    bullets.push_back(new peaBullet(plantRow,currentP.x+62, currentP.y+37, plants[i]->getAttackDamage(), currentScene));
						else if (plants[i]->getName() == DOUBLESHOOTER) {
							bullets.push_back(new peaBullet(plantRow, currentP.x + 62, currentP.y + 37, plants[i]->getAttackDamage(), currentScene));
							auto delay = DelayTime::create(0.4f);
							auto sequence = Sequence::create(delay, CallFunc::create([=]() {
								bullets.push_back(new peaBullet(plantRow, currentP.x + 62, currentP.y + 37, plants[i]->getAttackDamage(), currentScene));
								}), nullptr);
							plants[i]->getIdv()->runAction(sequence);
						}
						else if (isNight&&plants[i]->getName() == PUFF_SHROOM&&
							waiting[j]->getIdv()->getPosition().x - plants[i]->getX() <= 550) {
							bullets.push_back(new puffShroomBullet(1,plantRow, currentP.x + 250, currentP.y-5 , plants[i]->getAttackDamage(), currentScene));
						     }
						else if (isNight && plants[i]->getName() == FUME_SHROOM &&
							waiting[j]->getIdv()->getPosition().x - plants[i]->getX() <= 750) {
							bullets.push_back(new puffShroomBullet(2,plantRow, currentP.x + 380, currentP.y +35, plants[i]->getAttackDamage(), currentScene));
						     }
					}
				
				}
			}
		}
	}
}

//���bullet vector����û����Ҫɾ�����ӵ�
void God::checkBulletToDelete() {
	for (int i = 0; i < bullets.size(); i++) {//����ÿ���ӵ�
		if (bullets[i]->NeedRemove()) {//�������ӵ���Ҫ�Ƴ�
			std::vector<Bullet*>::iterator it = std::find(bullets.begin(), bullets.end(), bullets[i]);
			bullets.erase(it);//ѡ��erase������remove����Ϊ�˼���vector��������ʡ�ռ�
		}
	}
}

//д�º�����������⹽Ҫ��Ҫ����
void God::sunShroomGrowUp() {
	if (dayOrNight != NIGHT)
		return;
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getName() == SUN_SHROOM && plants[i]->IsAdolescent()) {
			long long int now = time(0);
			if (now - plants[i]->getPlantTime() >= 9) {
				plants[i]->growUp();
			}//90s����
		}
	}
}

//д�º�������������Ҫ��Ҫ��ը
void God::checkJalapenoBomb() {
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getCondition() == BOMB) {
			plants[i]->dieAnimation();
			new Flame(plants[i]->getRow(), plants[i]->getX(), plants[i]->getY(), plants[i]->getAttackDamage(), currentScene);
			for (int j = 0; j < waiting.size(); j++) {
				if (waiting[j]->getCol() == plants[i]->getRow()) {
					waiting[j]->setCondition(DEAD);
					waiting[j]->burning();
					//���˵Ķ����������˾Ͱ�������˵Ľ�ʬ��vector��ɾ��
					auto delay = DelayTime::create(3.0f);
					auto sequence = Sequence::create(delay, CallFunc::create([=]() {
						waiting[j]->getIdv()->removeFromParent(); //��ʬ���˲��Ƴ�
						}), nullptr);
					waiting[j]->getIdv()->runAction(sequence);
					//ֲ��ͽ�ʬ��ͬһ�У�����н�ʬ�����ű��ջٶ�����������������־
					//����û�аѻ������ӵ��ŵ��ӵ������У����������鲻��
				}
		    }
		}
	}
}

//д�º�����

//���̫�����ǲ��Ǹò���̫����
void God::checkSunflower()
{
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if ((plants[i]->getName() == SUNFLOWER|| plants[i]->getName() == SUN_SHROOM) &&
			plants[i]->getCondition() != DEAD &&plants[i]->getCondition() != SLEEP && plants[i]->canCreateSun()) {//��̫������û������û˯��
			
			if (plants[i]->getName() == SUNFLOWER) {//���Բ�����
				plants[i]->attackAnimation();//ֲ����ݷ���
				plants[i]->setCanNotCreateSun();//
				sun->flowerSun(plants[i]->getIdv()->getPosition(), 1);
			}
			else {

				if (plants[i]->IsAdolescent()) {
					sun->flowerSun(plants[i]->getIdv()->getPosition(), 0);
					plants[i]->setCanNotCreateSun();//
				}
				else {

					sun->flowerSun(plants[i]->getIdv()->getPosition(), 1);
					plants[i]->setCanNotCreateSun();//
				}
			}
			plants[i]->setCondition(HEALTHY);
			auto delay = DelayTime::create(5.0f);//ʮ���һ������
			auto sequence = Sequence::create(delay, CallFunc::create([=]() {
				plants[i]->setCanCreateSun();//��Ϊ�ܲ�����

				}), nullptr);
			plants[i]->getIdv()->runAction(sequence);
			
		}
	}
}

void God::checkCard()
{
	for (int i = 0; i < cards.size(); i++) {
		if (sun->getSunValue() >= cards[i]->getMoney()) {
			if (cards[i]->getCondition() != SLEEP) {//���û����
				cards[i]->setCondition(ABLE);
				cards[i]->changeApperence(1);
			}
		}
		else {
			cards[i]->setCondition(POOR);
			cards[i]->changeApperence(0);
		}
	}
}

void God::randomCardInit(Sun* _sun)
{
	int x = rand() % 1200 + 100;
	int y = rand() % 900 + 100;

	Card* rcard=new Card(x, 1400, 1.05, "empty", "empty.png", currentScene, MINIGAME, _sun,  dayOrNight);
	randCards.push_back(rcard);
	int speed = 150;
	auto moveBy = MoveBy::create((1400 - y) / speed, Vec2(0, -(1400 - y)));
	rcard->getIdv()->runAction(moveBy);
	Sprite* current = rcard->getIdv();

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([=]() {
		if (current && current->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			current->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	current->runAction(sequence);
	
}