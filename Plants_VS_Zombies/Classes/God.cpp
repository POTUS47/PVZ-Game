#include"God.h"
#include<algorithm>

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

//God的构造函数
God::God(int isNight, Scene* CurrentScene):dayOrNight(isNight),currentScene(CurrentScene) {
	sunNumber = 0;
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


	///////////////////////////////////////以下测试区域
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

	//检查发现，横向总共1920
	/* 植物的位置 纵坐标分别是160 350 540 730 920比较好（等差190）
	* 横坐标分别是 215 405...（等差190）
	* 植物的col=(x-160)/190+1
	*/

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
					waiting[i]->getIdv()->removeFromParent(); // 移动完成后移除子弹
					//waiting.erase(waiting.begin() + i);
					}), nullptr);
				waiting[i]->getIdv()->runAction(sequence);
			}
		}
		
	}
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
}

void God::setZombieStartTime()
{
	int num = waiting.size();
	for (int i = 0; i < num; i++) {
		float delayT = waiting[i]->getStartTime();
		auto delay = DelayTime::create(delayT);
		
		auto delayedCallback = CallFunc::create([=]() {
			waiting[i]->moveForward(waiting[i]->getIdv()); // 调用 moveForward 并传递 Sprite 参数
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
	for (int j = 0; j < waiting.size(); j++) {//遍历每一只僵尸
		if (waiting[j]->getCondition() == DEAD) {//如果死了就跳过
			continue;
		}
		Sprite* current = waiting[j]->getIdv();//僵尸的精灵指针
		int zombieRow = waiting[j]->getCol();
		for (int i = 0; i < littleCar.size(); i++) {//遍历每个车
			Sprite* car = littleCar[i]->getIdv();//车的精灵指针
			int carRow = littleCar[i]->getRow();//获取车所在的行
			if (zombieRow == carRow) {
				if (isIntersecting(current, car)) {//如果僵尸碰到车
					if (littleCar[waiting[j]->getCol() - 1]->getCondition() == NOTUSED) {//如果车没启动过
						littleCar[waiting[j]->getCol() - 1]->setCondition(USED);//标记为启动过
						auto delayAction = DelayTime::create(2);
						littleCar[waiting[j]->getCol() - 1]->carRun();
						car->runAction(delayAction);
					}
					else {//如果车启动了
						if (waiting[j]->getCondition() != WAIT) {//如果僵尸不是在等待区碰到了车
							waiting[j]->setHP(-100);
						}
						else {
							CCLOG("碰到一个等待僵尸");
						}
					}

				}
			}
		}
		
		
	}
}

//检查僵尸和子弹有没有相撞
void God::checkEat() {
	for (int i = 0; i < bullets.size(); i++) {//遍历所有子弹
		for (int j = 0; j<waiting.size(); j++) {//遍历所有僵尸
			if ((!bullets[i]->NeedRemove()) && (waiting[j]->getCondition() != DEAD)) {//如果子弹是需要被移除的就不再判断是否接触僵尸
				if (isIntersecting(bullets[i]->getIdv(), waiting[j]->getIdv())) {//如果子弹碰上僵尸
					int bulletRow = bullets[i]->getCol();//获取子弹所在第几行
					int zombieRow = waiting[j]->getCol();//获取僵尸在第几行
					if (bulletRow == zombieRow) {
						bullets[i]->explodeAnimation();//子弹爆炸特效，停留0.4秒后将子弹精灵从parent移除，然后标记为要从vector删除
						if (bullets[i]->getSEThp() == 0) {
							int currentHP = waiting[j]->getHP();
							waiting[j]->setHP(currentHP -= 20);//20需要改成植物的攻击能力
							bullets[i]->setSEThp(1);
						}
						
					}
				}
			}
			
		}
	}
}

//检查僵尸和植物有没有相撞（相撞意味着要吃植物）
void God::checkCrush() {
	for (int i = 0; i < plants.size(); i++) {
		for (int j = 0; j<waiting.size(); j++) {
			if (waiting[j]->getCondition() == DEAD) {
				continue;
			}
			if (isIntersecting(plants[i]->getIdv(), waiting[j]->getIdv())) {
				int plantRow = plants[i]->getRow();//获取植物所在第几行
				int zombieRow = waiting[j]->getCol();//获取僵尸在第几行
				if (plantRow == zombieRow) {//由于僵尸头会碰到上一行的植物，所以添加一个判断他们在同一行
					Sprite* thezombie = waiting[j]->getIdv();
					if (waiting[j]->getCondition() != EATING) {//如果现在没有在吃，就播放吃的画面
						waiting[j]->setCondition(EATING);
						waiting[j]->healthyEating(thezombie);
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
	for (int i = 0; i < plants.size(); i++) {//遍历植物
		if (plants[i]->getAttackDamage() != 0) {//筛出攻击性植物
			int plantRow = plants[i]->getRow();
			for (int j = 0; j<waiting.size(); j++) {//遍历所有僵尸
				if (waiting[j]->getCondition() != WAIT&& waiting[j]->getCondition() != DEAD) {//如果该僵尸不在等待区中
					int zombieRow = waiting[j]->getCol();
					if (zombieRow == plantRow) {//该植物启动攻击行为
						Vec2 currentP=plants[i]->getIdv()->getPosition();//获取要发射子弹的植物的位置
						bullets.push_back(new Bullet(plantRow,currentP.x, currentP.y, 5, currentScene));
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

//子弹加一个状态判断，如果需要被移除就不再判断有没有跟僵尸挨着