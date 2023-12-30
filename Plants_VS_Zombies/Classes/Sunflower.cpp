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
    //��������ֵ������
    setHealth(100);
    //��ֲ�￪ʼҡ��
	if (isNight)
		setCondition(SLEEP);
	waitingAnimation();
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

//ֲ��Ĺ��������������������� ����
void Sunflower::attackAnimation() {
	this->getIdv()->stopAllActions();
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 1; i < 15; i++)
	{
		sprintf(nameSize, "/plant/sunflower/(%d).png", i);
		animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
	}
	animation->setDelayPerUnit(0.07f);//����ÿ֡���ŵ�ʱ����
	animation->setLoops(1);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
	auto animate = Animate::create(animation);//������������

	auto sequence = Sequence::create(animate, CallFunc::create([=]() {
		waitingAnimation();
		}), nullptr);
	this->getIdv()->runAction(sequence);//����������Ӧ�õ������ϣ������ж���
	//��һ���ת�ؿ���ҡ��
	
}

