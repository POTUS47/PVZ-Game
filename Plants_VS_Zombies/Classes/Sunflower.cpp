#include "Sunflower.h"
extern int sunNumber;


Sunflower::Sunflower(int x, int y, double scale, Scene* scene,int isNight, Label* sunLightLabel):currentLevelSunLabel(sunLightLabel), theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
	setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
	setX(x);
	setY(y);
	setName(SUN_FLOWER);
	auto sunflower = cocos2d::Sprite::create("/plant/sunflower/SunFlower1.png");
    sunflower->setPosition(x, y);
    sunflower->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(sunflower, 2);
    setIdv(sunflower);//������ָ�����idv

    //��������ֵ������
    setHealth(100);
    //��ֲ�￪ʼҡ��
	if (isNight)
		waitingAnimation();
	else
		attackAnimation();
}

//ֲ��Ŀ���ҡ�ڶ���
void Sunflower::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/sunflower/SunFlower%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}

//ֲ��Ĺ�����������������
void Sunflower::attackAnimation() {
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 1; i < 9; i++)
	{
		sprintf(nameSize, "/plant/sunflower/SunFlower%d.png", i);
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
void Sunflower::dieAnimation() {
    this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}

void  Sunflower::createSun(float dt) {
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
	listener->onTouchBegan = [sun,sunLightLabel](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ������ⷶΧ��
		if (sun->getBoundingBox().containsPoint(touchLocation)) {
			// ���ⱻ�����ִ����ʧ�߼�
			sunNumber++;
			int sunlightCount = sunNumber * 25;// ����Label���ı�
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
	auto checkClickCallback = CallFunc::create([sun,scene]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);
}