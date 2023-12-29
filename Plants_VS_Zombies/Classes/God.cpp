#include"God.h"
#include<algorithm>
std::vector<Card*>cards;
std::vector<Card*>randCards;//随机卡片种子雨
/*小推车*/
std::vector<Car*>littleCar;
/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
std::vector<Zombie*>dead;


/*当前关卡的所有植物*/
std::vector<Plant*>plants;

std::vector<Bullet*>bullets;//子弹的数组
bool isIntersecting(Sprite* spriteA, Sprite* spriteB);//函数声明

/*数组储存出场时间*/
float Statime[2][3][10] = { 15,25,40,45,67,80,89,88,90,105,45,50,75,78,90,35,70,75,87};//level type number


//God的构造函数
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
}

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
	int totaldeath = 0;
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() == DEAD) {
			totaldeath++;
			if (totaldeath == 18) {
				//赢了
				exit(2);
			}
		}
		else {
			Vec2 currentPosition = waiting[i]->getIdv()->getPosition();
			if (currentPosition.x <= 0) {
				//输了
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
	//根据关卡的不同设置不同数量的僵尸
	if (level == 1) {
		normZ = 10;
		coneZ = 5;
		newsZ = 3;
	}
	else {

	}



	//开始生成僵尸,放入等待容器中
	//普通僵尸
	for (int i = 0; i < normZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new normalZombie(x, y, 2.0, currentScene));
	}
	//圆锥僵尸---
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
	//让所有等待区的僵尸进入等待状态，并设置出发时间，设置出发赛道
	for (int i = 0; i < waiting.size(); i++) {
		int col = rand() % 5 + 1;
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);//设置出发时间
		waiting[i]->setCol(col);//设置出发赛道
	}


	//检查发现，横向总共1920
/* 植物的位置 纵坐标分别是160 350 540 730 920比较好（等差190）
* 横坐标分别是 215 405...（等差190）
* 植物的row=(y-160)/190+1
*/
}

void God::dead()
{
	//检查是否有僵尸死亡
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() != DEAD) {//僵尸没死再检测
			if (waiting[i]->getHP() <= 0) {
				waiting[i]->setCondition(DEAD);
				waiting[i]->dieAndlay(waiting[i]->getIdv());
				//死了的动画播放完了就把这个死了的僵尸从vector里删掉
				auto delay = DelayTime::create(1.5f);
				auto sequence = Sequence::create(delay, CallFunc::create([=]() {
					waiting[i]->getIdv()->removeFromParent(); //僵尸死了不移除
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
			waiting[i]->moveForward(waiting[i]->getIdv()); // 调用 moveForward 并传递 Sprite 参数
			//waiting[i]->setCondition(WALKING);改为在moveforward里实现
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
						if (bullets[i]->condition == 0) {
							int currentHP = waiting[j]->getHP();
							int minus = bullets[i]->getDamgeVlue();
							waiting[j]->setHP(currentHP -= minus);
							bullets[i]->condition = 1;//保证一颗子弹只扣一次血，勿改勿改
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
			int plantRow = plants[i]->getRow();//获取植物所在第几行
			int zombieRow = waiting[j]->getCol();//获取僵尸在第几行

			if (zombieCon == WALKING) {//如果僵尸在走路的途中
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plants[i]-> getCondition()!=DEAD) {
						waiting[j]->setCondition(EATING);//僵尸变为在吃
						plants[i]->setEatCondition(BEINGEATEN);

						waiting[j]->healthyEating(waiting[j]->getIdv());
						//plants[i]->getHurt(waiting[j]->getAttack());///////////////////////////////////////////////////////具体数值需要再斟酌
					}
				}
			}
			else if (zombieCon == EATING) {//僵尸还在吃呢

				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plants[i]->getCondition() == DEAD) {//植物死了

						waiting[j]->moveForward(waiting[j]->getIdv());//僵尸变为走路
					}
					else if (plants[i]->getEatCondition() == BEINGEATEN) {//植物是被吃状态要扣血
						int attack = waiting[j]->getAttack();
						plants[i]->getHurt(attack);
						if (plants[i]->getCondition() == DEAD)
							continue;
						plants[i]->setEatCondition(NOT_EATEN);//一次只吃一次，扣完血变回健康状态
						auto delay = DelayTime::create(waiting[j]->getEatingTime());
						auto delayedCallback = CallFunc::create([=]() {
							plants[i]->setEatCondition(BEINGEATEN);//过一段时间变为被吃
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
	if (dayOrNight != NIGHT)
		return;
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getName() == SUN_SHROOM && plants[i]->IsAdolescent()) {
			long long int now = time(0);
			if (now - plants[i]->getPlantTime() >= 9) {
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

//写新函数：

//检查太阳花是不是该产生太阳了
void God::checkSunflower()
{
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if ((plants[i]->getName() == SUNFLOWER|| plants[i]->getName() == SUN_SHROOM) &&
			plants[i]->getCondition() != DEAD &&plants[i]->getCondition() != SLEEP && plants[i]->canCreateSun()) {//是太阳花且没有死且没睡觉
			
			if (plants[i]->getName() == SUNFLOWER) {//可以产阳光
				plants[i]->attackAnimation();//植物短暂发亮
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
			auto delay = DelayTime::create(5.0f);//十秒产一次阳光
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

	// 启动一个定时器，在五秒后检查是否有鼠标点击阳光，若无则自动消失
	float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([=]() {
		if (current && current->getParent()) {
			// 阳光还存在且没有被点击，则自动让阳光消失
			current->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	current->runAction(sequence);
	
}