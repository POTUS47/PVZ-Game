#include"God.h"
#include<algorithm>

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
float Statime[2][2][10] = {5,15,20,23,25,29,45,47,50,55};//level type number

int sunNumber = 0;

//God�Ĺ��캯��
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
	sunNumber = 0;
}

//������ÿ��0.1����øú���
void God::gameEnd()
{
	int totaldeath = 0;
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() == DEAD) {
			totaldeath++;
			if (totaldeath == 9) {
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
	//���ݹؿ��Ĳ�ͬ���ò�ͬ�����Ľ�ʬ
	if (level == 1) {
		normZ = 6;
		coneZ = 3;
	}
	else {

	}


	///////////////////////////////////////���²�������
	//plants.push_back(new PeaShooter(215, 350, 2.2, currentScene));
	//plants.push_back(new PeaShooter(405, 160, 2.2, currentScene));
	plants.push_back(new PeaShooter(595, 540, 2.2, currentScene));
	plants.push_back(new PeaShooter(785, 730, 2.2, currentScene));
	plants.push_back(new PeaShooter(975, 920, 2.2, currentScene));
	//plants.push_back(new PeaShooter(1165, 920, 2.2, currentScene));
	//plants.push_back(new PeaShooter(1335, 920, 2.2, currentScene));
	//plants.push_back(new PeaShooter(1545, 920, 2.2, currentScene));
	//plants.push_back(new PeaShooter(1735, 920, 2.2, currentScene));
	//new Bullet(300, 300, 5, currentScene);

	//��鷢�֣������ܹ�1920
	/* ֲ���λ�� ������ֱ���160 350 540 730 920�ȽϺã��Ȳ�190��
	* ������ֱ��� 215 405...���Ȳ�190��
	* ֲ���col=(x-160)/190+1
	*/

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
	//�����еȴ����Ľ�ʬ����ȴ�״̬�������ó���ʱ�䣬���ó�������
	for (int i = 0; i < waiting.size(); i++) {
		int col = rand() % 5 + 1;
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);//���ó���ʱ��
		waiting[i]->setCol(col);//���ó�������
	}
	
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
					waiting[i]->getIdv()->removeFromParent(); // �ƶ���ɺ��Ƴ��ӵ�
					//waiting.erase(waiting.begin() + i);
					}), nullptr);
				waiting[i]->getIdv()->runAction(sequence);
			}
		}
		
	}
	//����Ƿ���ֲ������//////////////////////////////������ͨ��gethurt��ʵ��
	for (int i = 0; i < walking.size(); i++) {
		if (plants[i]->getHealth() <= 0) {
			plants[i]->dieAnimation();
		}
	}
}

void God::updateSun()
{
	int sunlightCount = sunNumber * 25;

	// ����Label���ı�
	this->getSunLightLabel()->setString(" " + std::to_string(sunlightCount));
}


void God::createSun(Scene* scene)
{
	int x = rand() % 1200 + 100;
	int y = rand() % 900 + 100;

	auto sun = Sprite::create("1.png");
	sun->setPosition(x,1400);
	sun->setScale(2.0);
	scene->addChild(sun,2);

	auto animation = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i < 30; i++){
		sprintf(nameSize, "%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);
	}
	animation->setDelayPerUnit(0.03f);
	animation->setLoops(-1);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);

	sun->runAction(animate);
	int speed = 150;
	auto moveBy = MoveBy::create((1400-y)/speed, Vec2(0, -(1400-y)));
	sun->runAction(moveBy);

	
	// Ϊ������ӵ���¼�������
	Label* sunLabel=this->getSunLightLabel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun,this, sunLabel](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ������ⷶΧ��
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// ���ⱻ�����ִ����ʧ�߼�
			sunNumber++;
			this->updateSun();

			sun->stopAllActions();
			auto moveTo = MoveTo::create(0.5, Vec2(120, 1130));
			sun->runAction(moveTo);
			auto delayAction = DelayTime::create(0.8f);
			
			auto checkClickCallback = CallFunc::create([sun]() {
				sun->removeFromParent();
				});
			auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
			sun->runAction(sequence);
			
			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sun);

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	float t = (1400 - y) / speed+5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}

void God::setZombieStartTime()
{
	int num = waiting.size();
	for (int i = 0; i < num; i++) {
		float delayT = waiting[i]->getStartTime();
		auto delay = DelayTime::create(delayT);
		
		auto delayedCallback = CallFunc::create([=]() {
			waiting[i]->moveForward(waiting[i]->getIdv()); // ���� moveForward ������ Sprite ����
			waiting[i]->setCondition(WALKING);
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

void God::showCardinSeedBank(Scene* scene)
{
	Card peashooter(268, 1108, 1.95, "/card/peashooter.png", "1.png", scene);
	Card sunflower(380, 1108, 1.95, "/card/sunflower.png", "/plant/sunflower/SunFlower1.png",scene);
	Card nut(492, 1108, 1.95, "/card/nut.png", "/plant/nut/zz1.png", scene);
	Card repeatershooter(604, 1108, 1.95, "/card/repeatershooter.png", "/plant/doubleshooter/Repeater1.png", scene);
	//Card sunshroom(716, 1108, 1.95, "/card/sunshroom.png", scene);
	//Card jalapeno(828, 1108, 1.95, "/card/jalapeno.png", scene);
	//Card card_3(940, 1108, 1.95, "/card/card_3.png", scene);
	//Card card_4(1052, 1108, 1.95, "/card/card_4.png", scene);
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
		if (waiting[j]->getCondition() == DEAD) {//������˾�����
			continue;
		}
		Sprite* current = waiting[j]->getIdv();//��ʬ�ľ���ָ��
		int zombieRow = waiting[j]->getCol();
		for (int i = 0; i < littleCar.size(); i++) {//����ÿ����
			Sprite* car = littleCar[i]->getIdv();//���ľ���ָ��
			int carRow = littleCar[i]->getRow();//��ȡ�����ڵ���
			if (zombieRow == carRow) {
				if (isIntersecting(current, car)) {//�����ʬ������
					if (littleCar[waiting[j]->getCol() - 1]->getCondition() == NOTUSED) {//�����û������
						littleCar[waiting[j]->getCol() - 1]->setCondition(USED);//���Ϊ������
						auto delayAction = DelayTime::create(2);
						littleCar[waiting[j]->getCol() - 1]->carRun();
						car->runAction(delayAction);
					}
					else {//�����������
						if (waiting[j]->getCondition() != WAIT) {//�����ʬ�����ڵȴ��������˳�
							waiting[j]->setHP(-100);
						}
						else {
							CCLOG("����һ���ȴ���ʬ");
						}
					}

				}
			}
		}
		
		
	}
}

//��齩ʬ���ӵ���û����ײ
void God::checkEat() {
	for (int i = 0; i < bullets.size(); i++) {//���������ӵ�
		for (int j = 0; j<waiting.size(); j++) {//�������н�ʬ
			if ((!bullets[i]->NeedRemove()) && (waiting[j]->getCondition() != DEAD)) {//����ӵ�����Ҫ���Ƴ��ľͲ����ж��Ƿ�Ӵ���ʬ
				if (isIntersecting(bullets[i]->getIdv(), waiting[j]->getIdv())) {//����ӵ����Ͻ�ʬ
					int bulletRow = bullets[i]->getCol();//��ȡ�ӵ����ڵڼ���
					int zombieRow = waiting[j]->getCol();//��ȡ��ʬ�ڵڼ���
					if (bulletRow == zombieRow) {
						bullets[i]->explodeAnimation();//�ӵ���ը��Ч��ͣ��0.4����ӵ������parent�Ƴ���Ȼ����ΪҪ��vectorɾ��
						if (bullets[i]->getSEThp() == 0) {
							int currentHP = waiting[j]->getHP();
							waiting[j]->setHP(currentHP -= 20);//20��Ҫ�ĳ�ֲ��Ĺ�������
							bullets[i]->setSEThp(1);
						}
						
					}
				}
			}
			
		}
	}
}

//��齩ʬ��ֲ����û����ײ����ײ��ζ��Ҫ��ֲ�
void God::checkCrush() {
	for (int i = 0; i < plants.size(); i++) {
		for (int j = 0; j<waiting.size(); j++) {
			if (waiting[j]->getCondition() == DEAD) {
				continue;
			}
			if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv())) {
				int plantRow = plants[i]->getRow();//��ȡֲ�����ڵڼ���
				int zombieRow = waiting[j]->getCol();//��ȡ��ʬ�ڵڼ���
				if (plantRow == zombieRow) {//���ڽ�ʬͷ��������һ�е�ֲ��������һ���ж�������ͬһ��
					Sprite* thezombie = waiting[j]->getIdv();
					if (waiting[j]->getCondition() != EATING) {//�������û���ڳԣ��Ͳ��ųԵĻ���
						waiting[j]->setCondition(EATING);
						waiting[j]->healthyEating(thezombie);
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
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getAttackDamage() != 0) {//ɸ��������ֲ��
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//�������н�ʬ
				if (waiting[j]->getCondition() != WAIT&& waiting[j]->getCondition() != DEAD) {//����ý�ʬ���ڵȴ�����
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//��ֲ������������Ϊ
						Vec2 currentP=plants[i]->getIdv()->getPosition();//��ȡҪ�����ӵ���ֲ���λ��
						bullets.push_back(new Bullet(plantRow,currentP.x, currentP.y, 5, currentScene));
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

//�ӵ���һ��״̬�жϣ������Ҫ���Ƴ��Ͳ����ж���û�и���ʬ����