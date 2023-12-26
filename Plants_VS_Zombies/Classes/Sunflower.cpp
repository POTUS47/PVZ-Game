#include "Sunflower.h"
extern int sunNumber;


Sunflower::Sunflower(int x, int y, double scale, Scene* scene,int isNight, Label* sunLightLabel):currentLevelSunLabel(sunLightLabel), theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
	setCol((x - 215) / 190 + 1);//设置植物在哪一列出现
	setX(x);
	setY(y);
	setName(SUN_FLOWER);
	auto sunflower = cocos2d::Sprite::create("/plant/sunflower/SunFlower1.png");
    sunflower->setPosition(x, y);
    sunflower->setScale(scale);
    //添加到当前层
    scene->addChild(sunflower, 2);
    setIdv(sunflower);//将精灵指针存入idv

    //设置生命值等属性
    setHealth(100);
    //让植物开始摇摆
	if (isNight)
		waitingAnimation();
	else
		attackAnimation();
}

//植物的空闲摇摆动画
void Sunflower::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/sunflower/SunFlower%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//植物的工作动画：产生阳光
void Sunflower::attackAnimation() {
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 1; i < 9; i++)
	{
		sprintf(nameSize, "/plant/sunflower/SunFlower%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
	}
	animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
	animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
	//animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
	auto animate = Animate::create(animation);//创建动画动作
	this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
	//this->getScene()->schedule(schedule_selector(Sunflower::createSun), 15.0f);
	///////////////////////////////////////////////////////////错误
}

//植物死亡：消失
void Sunflower::dieAnimation() {
    this->getIdv()->removeFromParent();//让植物立刻消失在画面中
}

void  Sunflower::createSun(float dt) {
	int x = getRow();
	int y = getCol();

	auto sun = Sprite::create("1.png");
	sun->setPosition(x, y);
	sun->setScale(2.0);
	this->getScene()->addChild(sun, 2);
	//让阳光转起来
	auto animation = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i < 30; i++) {
		sprintf(nameSize, "%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);
	}
	animation->setDelayPerUnit(0.03f);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);
	sun->runAction(animate);

	// 为阳光添加点击事件监听器
	Label* sunLightLabel = this->getCurrentLevelSunLabel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun,sunLightLabel](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();

		// 判断点击位置是否在阳光范围内
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// 阳光被点击，执行消失逻辑
			sunNumber++;
			int sunlightCount = sunNumber * 25;// 更新Label的文本
			sunLightLabel->setString(" " + std::to_string(sunlightCount));

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
	auto delayAction = DelayTime::create(5);
	Scene* scene = this->getScene();
	auto checkClickCallback = CallFunc::create([sun,scene]() {
		if (sun && sun->getParent()) {
			// 阳光还存在且没有被点击，则自动让阳光消失
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}