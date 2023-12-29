#include"God.h"
<<<<<<< Updated upstream

=======
#include<algorithm>
std::vector<Card*>cards;
/*小推车*/
std::vector<Car*>littleCar;
>>>>>>> Stashed changes
/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
std::vector<Zombie*>dead;

/*当前关卡的所有植物*/
std::vector<Plant*>plants;

/*数组储存出场时间*/
float Statime[2][3][10] = { 15,25,40,45,67,80,89,88,90,105,45,50,75,78,90,35,70,75,87};//level type number

<<<<<<< Updated upstream
int sunNumber = 0;

//God的构造函数
God::God(int isNight):dayOrNight(isNight) {
	sunNumber = 0;
=======

//God的构造函数
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
>>>>>>> Stashed changes
}

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
<<<<<<< Updated upstream
	for (int i = 0; i < walking.size(); i++) {
		Sprite* current = walking[i]->getIdv();
		Vec2 pos= current->getPosition();
		if (pos.x <= 0) {
			exit(1);
			//调用gameover函数
=======
	int totaldeath = 0;
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() == DEAD) {
			totaldeath++;
			if (totaldeath == 18) {
				//赢了
				exit(2);
			}
>>>>>>> Stashed changes
		}
	}
}
////////////////////记得0.1s调用其他状态检查函数


void God::updateZombies(int level, Scene* scene)
{
	int normZ = 0;
<<<<<<< Updated upstream
	//根据关卡的不同设置不同数量的僵尸
	if (level == 1) {
		normZ = 5;
=======
	int coneZ = 0;
	int newsZ = 0;
	//根据关卡的不同设置不同数量的僵尸
	if (level == 1) {
		normZ = 10;
		coneZ = 5;
		newsZ = 3;
>>>>>>> Stashed changes
	}
	else {

	}

	//开始生成僵尸,放入等待容器中
	//普通僵尸
	for (int i = 0; i < normZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new normalZombie(x, y, 2.0, scene));
		plants.push_back(new PeaShooter(x-30, y-30, 2.2, scene));
		plants.push_back(new Nut(x -300, y - 80, 2.2, scene));
		plants.push_back(new DoubleShooter(x +40, y +80, 2.2, scene));
	}
	//圆锥僵尸---
<<<<<<< Updated upstream

=======
	for (int i = 0; i < coneZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new coneHeadZombie(x, y, 2.0, currentScene));
	}
	//报纸僵尸---
	for (int i = 0; i < newsZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new newspaperZombie(x, y, 2.0, currentScene));
	}
>>>>>>> Stashed changes
	//让所有等待区的僵尸进入等待状态，并设置出发时间，设置出发赛道
	for (int i = 0; i < waiting.size(); i++) {
		int col = rand() % 5 + 1;
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);//设置出发时间
		waiting[i]->setCol(col);//设置出发赛道
	}
<<<<<<< Updated upstream
	
=======
	plants.push_back(new DoubleShooter(215, 350, 2.2, currentScene));//////////////////////
	plants.push_back(new DoubleShooter(405, 160, 2.2, currentScene));//////////////////////
	plants.push_back(new Jalapeno(215, 160, 2.2, currentScene));

	plants.push_back(new PuffShroom(215, 730, 2.2, currentScene,1));/////////////
	plants.push_back(new PuffShroom(405, 920, 2.2, currentScene, 1));/////////////
	plants.push_back(new PuffShroom(595, 160, 2.2, currentScene, 1));/////////////
	plants.push_back(new PuffShroom(785, 350, 2.2, currentScene, 1));/////////////
	plants.push_back(new FumeShroom(975, 920, 2.2, currentScene, 1));/////////////


	//检查发现，横向总共1920
/* 植物的位置 纵坐标分别是160 350 540 730 920比较好（等差190）
* 横坐标分别是 215 405...（等差190）
* 植物的row=(y-160)/190+1
*/
>>>>>>> Stashed changes
}

void God::dead()
{
	//检查是否有僵尸死亡
	for (int i = 0; i < walking.size(); i++) {
		if (walking[i]->getHP() <= 0) {
			waiting[i]->dieAndlay(waiting[i]->getIdv());
		}
	}
<<<<<<< Updated upstream
	//检查是否有植物死亡//////////////////////////////这里想通过gethurt来实现
	for (int i = 0; i < walking.size(); i++) {
		if (plants[i]->getHealth() <= 0) {
			plants[i]->dieAnimation();
		}
	}
}

void God::updateSun()
{
	int sunlightCount = sunNumber * 25;

	// 更新Label的文本
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

	
	// 为阳光添加点击事件监听器
	Label* sunLabel=this->getSunLightLabel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun,this, sunLabel](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();

		// 判断点击位置是否在阳光范围内
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// 阳光被点击，执行消失逻辑
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

	// 启动一个定时器，在五秒后检查是否有鼠标点击阳光，若无则自动消失
	float t = (1400 - y) / speed+5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// 阳光还存在且没有被点击，则自动让阳光消失
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
=======
	//植物死亡已由植物类内函数处理
>>>>>>> Stashed changes
}

void God::setZombieStartTime()
{
	int num = waiting.size();
	for (int i = 0; i < num; i++) {
		float delayT = waiting[i]->getStartTime();
		auto delay = DelayTime::create(delayT);
		
		auto delayedCallback = CallFunc::create([=]() {
			waiting[i]->moveForward(waiting[i]->getIdv()); // 调用 moveForward 并传递 Sprite 参数
<<<<<<< Updated upstream
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

=======
			//waiting[i]->setCondition(WALKING);改为在moveforward里实现
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

void God::showCardinSeedBank(Scene* scene,Sun* _sun)
{

	cards.push_back(new Card(268, 1108, 1.95, "/card/peashooter", "/plant/peashooter/Peashooter1.png", scene,PEA_SHOOTER,_sun, dayOrNight));
	cards.push_back(new Card(380, 1108, 1.95, "/card/sunflower", "/plant/sunflower/SunFlower1.png", scene, SUNFLOWER, _sun, dayOrNight));
	cards.push_back(new Card(492, 1108, 1.95, "/card/nut", "/plant/nut/zz1.png", scene,NUT,_sun, dayOrNight));
	cards.push_back(new Card(604, 1108, 1.95, "/card/repeatershooter", "/plant/doubleshooter/Repeater1.png", scene,DOUBLE_SHOOTER,_sun, dayOrNight));
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
	for (int j = 0; j < waiting.size(); j++) {//遍历每一只僵尸
		int zombieCon = waiting[j]->getCondition();
		if (zombieCon == WALKING || zombieCon == EATING) {//只有正在走路和正在吃的僵尸会被撞
			for (int i = 0; i < littleCar.size(); i++) {//遍历每个车
				int zombieRow = waiting[j]->getCol();//获取僵尸的行
				int carRow = littleCar[i]->getRow();//获取车所在的行
				if (zombieRow == carRow&& isIntersecting(waiting[j]->getIdv(), littleCar[i]->getIdv())) {//只有在同一行才行而且要碰到
					if (littleCar[waiting[j]->getCol() - 1]->getCondition() == NOTUSED) {//如果车没启动过
						littleCar[waiting[j]->getCol() - 1]->setCondition(USED);//标记为启动过
						littleCar[waiting[j]->getCol() - 1]->carRun();
					}
					else {//如果车启动了
						waiting[j]->setHP(-100);
					}
				}
			}
		}
	}
}

//检查僵尸和子弹有没有相撞
void God::checkCrush() {
	for (int i = 0; i < bullets.size(); i++) {//遍历所有子弹
		for (int j = 0; j<waiting.size(); j++) {//遍历所有僵尸
			if ((!bullets[i]->NeedRemove()) && (waiting[j]->getCondition() != DEAD)) {//如果子弹是需要被移除的就不再判断是否接触僵尸
				if (isIntersecting(bullets[i]->getIdv(), waiting[j]->getIdv())) {//如果子弹碰上僵尸
					int bulletRow = bullets[i]->getRow();//获取子弹所在第几行
					int zombieRow = waiting[j]->getCol();//获取僵尸在第几行
					if (bulletRow == zombieRow) {
						bullets[i]->explodeAnimation();//子弹爆炸特效，停留0.4秒后将子弹精灵从parent移除，然后标记为要从vector删除
						if (bullets[i]->condition == NOT_USED) {
							int currentHP = waiting[j]->getHP();
							int minus = bullets[i]->getDamgeVlue();
							waiting[j]->setHP(currentHP -= minus);
							bullets[i]->condition = USED;//保证一颗子弹只扣一次血，勿改勿改
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
			int plantCon = plants[i]->getCondition();
			int plantRow = plants[i]->getRow();//获取植物所在第几行
			int zombieRow = waiting[j]->getCol();//获取僵尸在第几行

			if (zombieCon == WALKING) {//如果僵尸在走路的途中
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plantCon == HEALTHY||plantCon==SLEEP) {
						waiting[j]->setCondition(EATING);//僵尸变为在吃
						plants[i]->setCondition(BEINGEATEN);
						waiting[j]->healthyEating(waiting[j]->getIdv());
						//plants[i]->getHurt(waiting[j]->getAttack());///////////////////////////////////////////////////////具体数值需要再斟酌
					}
				}
			}
			else if (zombieCon == EATING) {//僵尸还在吃呢
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plantCon == DEAD) {//植物死了
						waiting[j]->moveForward(waiting[j]->getIdv());//僵尸变为走路
					}
					else if (plantCon == BEINGEATEN) {//植物是被吃状态要扣血
						int currenthp = plants[i]->getHealth();
						int attack = waiting[j]->getAttack();
						plants[i]->setHealth(currenthp -= attack);
						plants[i]->setCondition(HEALTHY);//一次只吃一次，扣完血变回健康状态
						auto delay = DelayTime::create(waiting[j]->getEatingTime());
						auto delayedCallback = CallFunc::create([=]() {
							plants[i]->setCondition(BEINGEATEN);//过一段时间变为被吃
							});
						auto sequence = Sequence::create(delay, delayedCallback, nullptr);
						plants[i]->getIdv()->runAction(sequence);
					}
				}
			}
		}
	}

}

//用于检测两精灵有无相遇的辅助函数
bool isIntersecting(Sprite* spriteA, Sprite* spriteB) {
	Rect rectA = spriteA->getBoundingBox();
	Rect rectB = spriteB->getBoundingBox();

	return rectA.intersectsRect(rectB);
}

//检查植物需不需要发射子弹,可以2s检查一次？
void God::checkAttack() {
	int isNight = dayOrNight;
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getAttackDamage() != 0&&plants[i]->getCondition()!=DEAD&& plants[i]->getCondition() != SLEEP) {//筛出攻击性植物且植物不能死亡
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//遍历所有僵尸
				if (waiting[j]->getCondition() == WALKING|| waiting[j]->getCondition() ==EATING) {//得到活着的或者正在吃的僵尸
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//该植物启动攻击行为
						Vec2 currentP=plants[i]->getIdv()->getPosition();//获取要发射子弹的植物的位置
						if(plants[i]->getName()==PEA_SHOOTER)
						    bullets.push_back(new peaBullet(plantRow,currentP.x+62, currentP.y+37, plants[i]->getAttackDamage(), currentScene));
						else if (plants[i]->getName() == DOUBLE_SHOOTER) {
							bullets.push_back(new peaBullet(plantRow, currentP.x + 62, currentP.y + 37, plants[i]->getAttackDamage(), currentScene));
							auto delay = DelayTime::create(0.3f);
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

//检查bullet vector中有没有需要删除的子弹
void God::checkBulletToDelete() {
	for (int i = 0; i < bullets.size(); i++) {//遍历每个子弹
		if (bullets[i]->NeedRemove()) {//如果这颗子弹需要移除
			std::vector<Bullet*>::iterator it = std::find(bullets.begin(), bullets.end(), bullets[i]);
			bullets.erase(it);//选用erase而不用remove是是为了减少vector容量，节省空间
		}
	}
}

//写新函数：检查阳光菇要不要生长
void God::sunShroomGrowUp() {

	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getName()==SUN_SHROOM&&plants[i]->IsAdolescent()) {
			long long int now = time(0);
			if (now - plants[i]->getPlantTime() >= 90) {
				plants[i]->growUp();
			}//90s长大
		}
	}
}

//写新函数：检测火爆辣椒要不要爆炸
void God::checkJalapenoBomb() {
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getCondition() == BOMB) {
			plants[i]->dieAnimation();
			new Flame(plants[i]->getRow(), plants[i]->getX(), plants[i]->getY(), plants[i]->getAttackDamage(), currentScene);
			for (int j = 0; j < waiting.size(); j++) {
				if (waiting[j]->getCol() == plants[i]->getRow()) {
					waiting[j]->setCondition(DEAD);
					waiting[j]->burning();
					//死了的动画播放完了就把这个死了的僵尸从vector里删掉
					auto delay = DelayTime::create(3.0f);
					auto sequence = Sequence::create(delay, CallFunc::create([=]() {
						waiting[j]->getIdv()->removeFromParent(); //僵尸死了不移除
						}), nullptr);
					waiting[j]->getIdv()->runAction(sequence);
					//植物和僵尸在同一行，则该行僵尸均播放被烧毁动画，且设置死亡标志
					//这里没有把火爆辣椒子弹放到子弹数组中，其他函数查不到
				}
		    }
		}
	}
}

//检查太阳花和阳光菇是不是该产生太阳了
void God::checkSunflower()
{
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if ((plants[i]->getName() == SUNFLOWER|| plants[i]->getName() == SUN_SHROOM)
			&& plants[i]->getCondition() != DEAD&& plants[i]->canCreateSun()) {//是太阳花且没有死且能产阳光
			if (plants[i]->getName() == SUNFLOWER && dayOrNight != NIGHT) {
				plants[i]->attackAnimation();//植物短暂发亮
				plants[i]->setCanNotCreateSun();//
				sun->flowerSun(plants[i]->getIdv()->getPosition(), 1);
			}
			else {
				if (dayOrNight == NIGHT) {
					if (plants[i]->IsAdolescent()) {
						sun->flowerSun(plants[i]->getIdv()->getPosition(), 1);
					}
					else {
						sun->flowerSun(plants[i]->getIdv()->getPosition(), 0);
					}
				}
			}
			plants[i]->setCondition(HEALTHY);
			auto delay = DelayTime::create(20.0f);//十秒产一次阳光
			auto sequence = Sequence::create(delay, CallFunc::create([=]() {
				plants[i]->setCanCreateSun();//设为能产阳光
				}), nullptr);
			plants[i]->getIdv()->runAction(sequence);
		}
	}
}

void God::checkCard()
{
	for (int i = 0; i < cards.size(); i++) {
		if (sun->getSunValue() >= cards[i]->getMoney()) {
			if (cards[i]->getCondition() != SLEEP) {//如果没休眠
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

///////////////////记得在level的析构函数中清空vector 释放内存
>>>>>>> Stashed changes
