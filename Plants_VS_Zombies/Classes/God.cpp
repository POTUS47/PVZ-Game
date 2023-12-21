#include"God.h"

/*正在等待的僵尸*/
std::vector<Zombie*>waiting;
/*出场的僵尸*/
std::vector<Zombie*>walking;
/*死了的僵尸*/
std::vector<Zombie*>dead;
/*数组储存出场时间*/
float Statime[2][2][10] = {1,25,50,60,70,40,45,47,50,55 };//level type number

int sunNumber = 0;

//God的构造函数
God::God() {
	sunNumber = 0;
}

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
	for (int i = 0; i < waiting.size(); i++) {
		waiting[i]->standBy(waiting[i]->getIdv());
		waiting[i]->setStartTime(Statime[level-1][1-1][i]);
	}
	//waiting[2]->loseHead(waiting[2]->getIdv());
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
	int y = rand() % 800 + 1;

	auto sun = Sprite::create("1.png");
	sun->setPosition(x,1000);
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
	auto moveBy = MoveBy::create(5, Vec2(0, -1000));
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
	auto delayAction = DelayTime::create(10.0f);
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

