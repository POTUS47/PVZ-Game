#include "SunShroom.h"


//�������⹽
SunShroom::SunShroom(int x, int y, double scale, Scene* scene, int isNight) : theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
	setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
	setX(x);
	setY(y);
	setName (SUN_SHROOM);
	setPlantTime( time(0));//��ȡ���⹽���ֵ�ʱ��
	auto sunshroom = cocos2d::Sprite::create("/plant/sunshroom/s1.png");
	sunshroom->setPosition(x, y);
	sunshroom->setScale(scale);
	//��ӵ���ǰ��
	scene->addChild(sunshroom, 2);
	setIdv(sunshroom);//������ָ�����idv
	setCondition(ABLE);//����Ϊ���Բ�����
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
	this->getIdv()->stopAllActions();
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
	this->setCondition(DEAD);
	getIdv()->setVisible(false);
	//this->getIdv()->removeFromParent();//��ֲ��������ʧ�ڻ�����
}


void  SunShroom::growUp() {
	bigAnimation();
}
