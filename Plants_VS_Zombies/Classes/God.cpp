#include"God.h"
#include<algorithm>
std::vector<Card*>cards;
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
float Statime[2][2][10] = {5,15,20,23,25,29,45,47,50,55};//level type number

int sunNumber = 0;
int littleSunNumber = 0;//全局变量，记录大阳光（25）和小阳光（15）的个数，方便更新阳光标签

//God的构造函数
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
	sunNumber = 0;
	littleSunNumber = 0;//每开一新关卡，阳光数清零
}

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
	int totaldeath = 0;
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i]->getCondition() == DEAD) {
			totaldeath++;
			if (totaldeath == 9) {
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
	//根据关卡的不同设置不同数量的僵尸
	if (level == 1) {
		normZ = 6;
		coneZ = 3;
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
	//让所有等待区的僵尸进入等待状态，并设置出发时间，设置出发赛道
	for (int i = 0; i < waiting.size(); i++) {
		int col = rand() % 5 + 1;
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);//设置出发时间
		waiting[i]->setCol(col);//设置出发赛道
	}
	
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
		}
		
	}
	//检查是否有植物死亡
	for (int i = 0; i < plants.size(); i++) {
		if (plants[i]->getCondition() != DEAD) {//如果植物没死
			if (plants[i]->getHealth() <= 0) {
				plants[i]->setCondition(DEAD);//设置为死了
				//plants[i]->dieAnimation();//植物立刻消失，移除精灵指针
				//甚至不能移除指针，我先用设置为隐形替代（勿改）
				plants[i]->getIdv()->setVisible(false);
			}
		}
	}
}

void God::updateSun()
{
	int sunlightCount = sunNumber * 25 + littleSunNumber * 15;

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
					bullets[i]->explodeAnimation();//子弹爆炸特效，停留0.2秒后将子弹精灵从parent移除，然后标记为要从vector删除
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
			int plantRow = plants[i]->getRow();//获取植物所在第几行
			int zombieRow = waiting[j]->getCol();//获取僵尸在第几行
			if (zombieCon == WALKING) {//如果僵尸在走路的途中
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plantCon == HEALTHY) {
						waiting[j]->setCondition(EATING);//僵尸变为在吃
						waiting[j]->healthyEating(waiting[j]->getIdv());
						plants[i]->getHurt(waiting[j]->getAttack());///////////////////////////////////////////////////////具体数值需要再斟酌
					}
				}
			}
			else if (zombieCon == EATING) {//僵尸还在吃呢
				if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv()) && zombieRow == plantRow) {//碰上植物且在同一行
					if (plantCon == DEAD) {//植物死了
						waiting[j]->moveForward(waiting[j]->getIdv());//僵尸变为走路
					}
					else {//植物是被吃状态要扣血
						plants[i]->getHurt(waiting[j]->getAttack());
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

//检查豌豆射手需不需要发射子弹,可以2s检查一次？
void God::checkAttack() {
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getAttackDamage() != 0&&plants[i]->getCondition()!=DEAD) {//筛出攻击性植物且植物不能死亡
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//遍历所有僵尸
				if (waiting[j]->getCondition() == WALKING|| waiting[j]->getCondition() ==EATING) {//得到活着的或者正在吃的僵尸
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//该植物启动攻击行为
						Vec2 currentP=plants[i]->getIdv()->getPosition();//获取要发射子弹的植物的位置
						if(plants[i]->getName()==PEA_SHOOTER)
						    bullets.push_back(new peaBullet(plantRow,currentP.x+62, currentP.y+37, plants[i]->getAttackDamage(), currentScene));
						else if (plants[i]->getName() == DOUBLE_SHOOTER) {
							//想办法 发射两发子弹
						}
						else{

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
				if (waiting[i]->getCol() == plants[i]->getRow()) {
					//植物和僵尸在同一行，则该行僵尸均播放被烧毁动画，且设置死亡标志
					//这里没有把火爆辣椒子弹放到子弹数组中，其他函数查不到
				}
		    }
		}
	}
}