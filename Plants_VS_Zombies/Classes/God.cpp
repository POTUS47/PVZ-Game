#include"God.h"
#include<algorithm>
std::vector<Card*>cards;
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
int littleSunNumber = 0;//ȫ�ֱ�������¼�����⣨25����С���⣨15���ĸ�����������������ǩ

//God�Ĺ��캯��
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
	sunNumber = 0;
	littleSunNumber = 0;//ÿ��һ�¹ؿ�������������
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
					waiting[i]->getIdv()->removeFromParent(); //��ʬ���˲��Ƴ�
					//waiting.erase(waiting.begin() + i);
					}), nullptr);
				waiting[i]->getIdv()->runAction(sequence);
			}
		}
		
	}
	//����Ƿ���ֲ������
	for (int i = 0; i < plants.size(); i++) {
		if (plants[i]->getCondition() != DEAD) {//���ֲ��û��
			if (plants[i]->getHealth() <= 0) {
				plants[i]->setCondition(DEAD);//����Ϊ����
				//plants[i]->dieAnimation();//ֲ��������ʧ���Ƴ�����ָ��
				//���������Ƴ�ָ�룬����������Ϊ�����������ģ�
				plants[i]->getIdv()->setVisible(false);
			}
		}
	}
}

void God::updateSun()
{
	int sunlightCount = sunNumber * 25 + littleSunNumber * 15;

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
			//waiting[i]->setCondition(WALKING);��Ϊ��moveforward��ʵ��
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

void God::showCardinSeedBank(Scene* scene)
{
	cards.push_back(new Card(268, 1108, 1.95, "/card/peashooter.png", "1.png", scene,PEASHOOTER));
	cards.push_back(new Card(380, 1108, 1.95, "/card/sunflower.png", "/plant/sunflower/SunFlower1.png", scene,SUNFLOWER));
	cards.push_back(new Card(492, 1108, 1.95, "/card/nut.png", "/plant/nut/zz1.png", scene,NUT));
	cards.push_back(new Card(604, 1108, 1.95, "/card/repeatershooter.png", "/plant/doubleshooter/Repeater1.png", scene,DOUBLESHOOTER));
	 //peashooter(268, 1108, 1.95, "/card/peashooter.png", "1.png", scene);
	//Card sunflower(380, 1108, 1.95, "/card/sunflower.png", "/plant/sunflower/SunFlower1.png",scene);
	//Card nut(492, 1108, 1.95, "/card/nut.png", "/plant/nut/zz1.png", scene);
	//Card repeatershooter(604, 1108, 1.95, "/card/repeatershooter.png", "/plant/doubleshooter/Repeater1.png", scene);
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
					bullets[i]->explodeAnimation();//�ӵ���ը��Ч��ͣ��0.2����ӵ������parent�Ƴ���Ȼ����ΪҪ��vectorɾ��
					int currentHP = waiting[j]->getHP();
					waiting[j]->setHP(currentHP -= bullets[i]->getDamgeVlue());
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
			int plantCon = plants[i]->getCondition();
			int plantRow = plants[i]->getRow();//��ȡֲ�����ڵڼ���
			int zombieRow = waiting[j]->getCol();//��ȡ��ʬ�ڵڼ���
			if (zombieCon == WALKING) {//�����ʬ����·��;��
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//����ֲ������ͬһ��
					if (plantCon == HEALTHY) {
						waiting[j]->setCondition(EATING);//��ʬ��Ϊ�ڳ�
						waiting[j]->healthyEating(waiting[j]->getIdv());
						plants[i]->getHurt(waiting[j]->getAttack());///////////////////////////////////////////////////////������ֵ��Ҫ������
					}
				}
			}
			else if (zombieCon == EATING) {//��ʬ���ڳ���
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//����ֲ������ͬһ��
					if (plantCon == DEAD) {//ֲ������
						waiting[j]->moveForward(waiting[j]->getIdv());//��ʬ��Ϊ��·
					}
					else {//ֲ���Ǳ���״̬Ҫ��Ѫ
						plants[i]->getHurt(waiting[j]->getAttack());
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

//����㶹�����費��Ҫ�����ӵ�,����2s���һ�Σ�
void God::checkAttack() {
	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getAttackDamage() != 0&&plants[i]->getCondition()!=DEAD) {//ɸ��������ֲ����ֲ�ﲻ������
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//�������н�ʬ
				if (waiting[j]->getCondition() == WALKING|| waiting[j]->getCondition() ==EATING) {//�õ����ŵĻ������ڳԵĽ�ʬ
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//��ֲ������������Ϊ
						Vec2 currentP=plants[i]->getIdv()->getPosition();//��ȡҪ�����ӵ���ֲ���λ��
						if(plants[i]->getName()==PEA_SHOOTER)
						    bullets.push_back(new peaBullet(plantRow,currentP.x+62, currentP.y+37, plants[i]->getAttackDamage(), currentScene));
						else if (plants[i]->getName() == DOUBLE_SHOOTER) {
							//��취 ���������ӵ�
						}
						else{

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

	for (int i = 0; i < plants.size(); i++) {//����ֲ��
		if (plants[i]->getName()==SUN_SHROOM&&plants[i]->IsAdolescent()) {
			long long int now = time(0);
			if (now - plants[i]->getPlantTime() >= 90) {
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
				if (waiting[i]->getCol() == plants[i]->getRow()) {
					//ֲ��ͽ�ʬ��ͬһ�У�����н�ʬ�����ű��ջٶ�����������������־
					//����û�аѻ������ӵ��ŵ��ӵ������У����������鲻��
				}
		    }
		}
	}
}