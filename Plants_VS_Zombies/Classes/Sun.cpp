#include"Sun.h"


Sun::Sun(Scene* scene)
{
	sunLightLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	sunLightLabel->setPosition(Vec2(115, 1038));  // ����Label��λ��
	sunLightLabel->setTextColor(Color4B::BLACK);  // ����������ɫΪ��ɫ
	scene->addChild(sunLightLabel, 2);  // ��Label��ӵ�������
	currentScene = scene;//�����˵�ǰ�ĳ����Ժ������
	sunValue = 0;
}

void Sun::updateSun()
{
	//sunValue = sunNumber * 25 + littleSunNumber * 15;
	// ����Label���ı�
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


	// Ϊ������ӵ���¼�������
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun, this](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ������ⷶΧ��
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// ���ⱻ�����ִ����ʧ�߼�
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

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}