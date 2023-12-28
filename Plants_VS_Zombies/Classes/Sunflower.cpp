#include "Sunflower.h"


Sunflower::Sunflower(int x, int y, double scale, Scene* scene,int isNight):theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
	setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
	setX(x);
	setY(y);
	setName(SUNFLOWER);
	auto sunflower = cocos2d::Sprite::create("/plant/sunflower/SunFlower1.png");
    sunflower->setPosition(x, y);
    sunflower->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(sunflower, 2);
    setIdv(sunflower);//������ָ�����idv
	setCondition(ABLE);//����Ϊ���Բ�����
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
	this->setCondition(PLANT_SLEEP);
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
	
}

//ֲ����������ʧ
void Sunflower::dieAnimation() {
	this->setCondition(DEAD);

   this->getIdv()->setVisible(false);//��ֲ��������ʧ�ڻ�����
}
