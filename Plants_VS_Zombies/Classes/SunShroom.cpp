#include "SunShroom.h"
extern int sunNumber;
extern int littleSunNumber;

//�������⹽
SunShroom::SunShroom(int x, int y, double scale, Scene* scene, int isNight, Label* sunLightLabel) :currentLevelSunLabel(sunLightLabel), theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
	setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
	setX(x);
	setY(y);
	setName (SUN_SHROOM);
	plantTime = time(0);//��ȡ���⹽���ֵ�ʱ��
	auto sunshroom = cocos2d::Sprite::create("/plant/sunshroom/s0.png");
	sunshroom->setPosition(x, y);
	sunshroom->setScale(scale);
	//��ӵ���ǰ��
	scene->addChild(sunshroom, 2);
	setIdv(sunshroom);//������ָ�����idv

	//��������ֵ������
	setHealth(100);
	//��ֲ�￪ʼҡ��
	if (!isNight)
		waitingAnimation();
	else
		littleAnimation();
}

//ֲ���˯������
void SunShroom::waitingAnimation() {

	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/s%d", i);
		animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
	}
	animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
	animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
	//animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
	auto animate = Animate::create(animation);//������������
	this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//С���⹽������
void SunShroom::littleAnimation() {
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/l%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
	}
	animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
	animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
	//animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
	auto animate = Animate::create(animation);//������������
	this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
	//this->getScene()->schedule(schedule_selector(Sunflower::createLittleSun), 15.0f);
	///////////////////////////////////////////////////////////����
}

//�����⹽������(
void SunShroom::bigAnimation() {
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/b%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
	}
	animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
	animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
	//animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
	auto animate = Animate::create(animation);//������������
	this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
	//this->getScene()->schedule(schedule_selector(Sunflower::createSun), 15.0f);
	///////////////////////////////////////////////////////////����
}

//ֲ����������ʧ
void SunShroom::dieAnimation() {
	this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}

//����25������
void  SunShroom::createSun(float dt) {
	int x = getRow();
	int y = getCol();

	auto sun = Sprite::create("1.png");
	sun->setPosition(x, y);
	sun->setScale(2.0);
	this->getScene()->addChild(sun, 2);
	//������ת����
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

	// Ϊ������ӵ���¼�������
	Label* sunLightLabel = this->getCurrentLevelSunLabel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun, sunLightLabel](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ������ⷶΧ��
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// ���ⱻ�����ִ����ʧ�߼�
			sunNumber++;
			int sunlightCount = sunNumber * 25 + littleSunNumber * 15;// ����Label���ı�
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

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	auto delayAction = DelayTime::create(5);
	Scene* scene = this->getScene();
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}

//����15С���⡣�ı������scale�Լ���ǩ���ӵ���ֵ����
void  SunShroom::createLittleSun(float dt) {
	int x = getRow();
	int y = getCol();

	auto sun = Sprite::create("1.png");
	sun->setPosition(x, y);
	sun->setScale(1.0);//�ı���scale
	this->getScene()->addChild(sun, 2);
	//������ת����
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

	// Ϊ������ӵ���¼�������
	Label* sunLightLabel = this->getCurrentLevelSunLabel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [sun, sunLightLabel](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ������ⷶΧ��
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// ���ⱻ�����ִ����ʧ�߼�
			littleSunNumber++;
			int sunlightCount = sunNumber * 25 + littleSunNumber * 15;;// ����Label���ı�
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

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	auto delayAction = DelayTime::create(5);
	Scene* scene = this->getScene();
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}
