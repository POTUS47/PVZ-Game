#include"God.h"
/*小推车*/
std::vector<Car*>littleCar;
/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
std::vector<Zombie*>dead;
/*数组储存出场时间*/
float Statime[2][2][10] = {5,15,20,23,25,29,30,33,35,40};//level type number

int sunNumber = 0;

//God的构造函数
God::God() {
	sunNumber = 0;
}

//调度器每隔0.1秒调用该函数
void God::gameEnd()
{
	for (int i = 0; i < waiting.size(); i++) {
		Sprite* current = waiting[i]->getIdv();
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
		waiting.push_back(new normalZombie(x, y, 2.0, scene));
	}
	//圆锥僵尸---
	for (int i = 0; i < coneZ; i++) {
		int x = rand() % 300 + 1400;
		int y = rand() % 800 + 100;
		waiting.push_back(new coneHeadZombie(x, y, 2.0, scene));
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
	for (int i = 0; i < walking.size(); i++) {
		if (walking[i]->getHP() <= 0) {
			waiting[i]->dieAndlay(waiting[i]->getIdv());
		}
	}
}

void God::updateSun(Label* sunlightLabel)
{
	int sunlightCount = sunNumber * 25;

	// 更新Label的文本
	sunlightLabel->setString(" " + std::to_string(sunlightCount));
}


void God::createSun(Scene* scene,Label*sunLightLabel)
{
	int x = rand() % 1200 + 100;
	int y = rand() % 900 + 100;

	auto sun = Sprite::create("1.png");
	sun->setPosition(x,1400);
	sun->setScale(2.0);
	scene->addChild(sun,4);

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
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun,this,sunLightLabel](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();

		// 判断点击位置是否在阳光范围内
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// 阳光被点击，执行消失逻辑
			sunNumber++;
			this->updateSun(sunLightLabel);
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
			});
		auto sequence = Sequence::create(delay, delayedCallback, nullptr);
		(waiting[i]->getIdv())->runAction(sequence);
	}
}

void God::showCardinSeedBank(Scene*scene)
{
	Card peashooter(268, 1108, 1.95, "/card/peashooter.png",scene);
	Card sunflower(380, 1108, 1.95, "/card/sunflower.png", scene);
	Card nut(492, 1108, 1.95, "/card/nut.png", scene);
	Card repeatershooter(604, 1108, 1.95, "/card/repeatershooter.png", scene);
	Card sunshroom(716, 1108, 1.95, "/card/sunshroom.png", scene);
	Card jalapeno(828, 1108, 1.95, "/card/jalapeno.png", scene);
	Card card_3(940, 1108, 1.95, "/card/card_3.png", scene);
	Card card_4(1052, 1108, 1.95, "/card/card_4.png", scene);
}

void God::initCar(Scene* scene)
{
	for (int i = 1; i < 6; i++) {
		littleCar.push_back(new Car(i,scene));
	}
}

void God::hitByCar()
{
	for (int j = 0; j < waiting.size(); j++) {//遍历每一只僵尸
		Sprite* current = waiting[j]->getIdv();
		if (current->getBoundingBox().containsPoint(Vec2(80, current->getPosition().y))) {
			Sprite* car = littleCar[waiting[j]->getCol() - 1]->getIdv();
			if (car!=nullptr) {
				auto delayAction = DelayTime::create(2);
				auto checkClickCallback = CallFunc::create([=]() {
					car->removeFromParent();
					});
				auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
				littleCar[waiting[j]->getCol() - 1]->carRun();
				car->runAction(sequence);
			}
			
		}	
	}
}