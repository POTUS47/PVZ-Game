#include"Sun.h"


Sun::Sun(Scene* scene)
{
	sunLightLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	sunLightLabel->setPosition(Vec2(115, 1038));  // 设置Label的位置
	sunLightLabel->setTextColor(Color4B::BLACK);  // 设置字体颜色为黑色
	scene->addChild(sunLightLabel, 2);  // 将Label添加到场景中
	currentScene = scene;//存下了当前的场景以后可以用
	sunValue = 0;
}

void Sun::updateSun()
{
	//sunValue = sunNumber * 25 + littleSunNumber * 15;
	// 更新Label的文本
	sunLightLabel->setString(" " + std::to_string(sunValue));
}


void Sun::createSun()
{
	int x = rand() % 1200 + 100;
	int y = rand() % 900 + 100;

	auto sun = Sprite::create("1.png");
	sun->setPosition(x, 1400);
	sun->setScale(2.0);
	currentScene->addChild(sun, 2);

	auto animation = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i < 30; i++) {
		sprintf(nameSize, "%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);
	}
	animation->setDelayPerUnit(0.03f);
	animation->setLoops(-1);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);

	sun->runAction(animate);
	int speed = 150;
	auto moveBy = MoveBy::create((1400 - y) / speed, Vec2(0, -(1400 - y)));
	sun->runAction(moveBy);


	// 为阳光添加点击事件监听器
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun, this](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();

		// 判断点击位置是否在阳光范围内
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// 阳光被点击，执行消失逻辑
			sunValue+=25;
			updateSun();

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
	float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun]() {
		if (sun && sun->getParent()) {
			// 阳光还存在且没有被点击，则自动让阳光消失
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}