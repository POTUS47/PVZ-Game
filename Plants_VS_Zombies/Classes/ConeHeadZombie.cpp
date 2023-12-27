#include"ConeHeadZombie.h"
USING_NS_CC;

//Բ׶��ʬ�Ĺ��캯��
//������ʼλ�� ���Ŵ�С
coneHeadZombie::coneHeadZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(30);
    setWeapen(true);
    setCondition(WAIT);
    setHP(120);
    setAttack(25);
    setEatingTime(0.8f);
    auto conezombie = cocos2d::Sprite::create("/conehead/standby/1.png");
    conezombie->setPosition(x, y);
    conezombie->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(conezombie, 2);
    setIdv(conezombie);//������ָ�����idv
}

void coneHeadZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/conehead/standby/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void coneHeadZombie::healthyEating(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
    
    char healthyattackarray[40] = { 0 };
    if (getWeapen() == true) {//������ڻ�������
        for (int i = 1; i < 12; i++)
        {
            sprintf(healthyattackarray, "/conehead/healthyeating/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    else {//���û�����ˣ�ñ�ӵ��ˣ�
        for (int i = 1; i < 22; i++)
        {
            sprintf(healthyattackarray, "/normalzombie/healthyattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);//ѭ������
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim = Animate::create(animation);
    who->runAction(anim);
}

/**
* @param �������ĸ�����Ҫ��ǰ��
* @return void
*/
void coneHeadZombie::moveForward(Sprite* who)
{
    if (getCondition() == WAIT) {//����Ǵӵȴ�����Ϊ��ǰ��
        int starty = getCol();
        who->setPosition(1950, starty * 200 - 10);//��Ҫ���ó���λ��
    }
    setCondition(WALKING);
    who->stopAllActions();
    auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
    who->runAction(moveBy);
    auto animation = Animation::create();
    char nameSize[40] = { 0 };
    if (getWeapen() == true) {//������ڻ�������
        for (int i = 1; i < 22; i++)
        {
            sprintf(nameSize, "/conehead/walking/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    }
    else {//���û�����ˣ�ñ�ӵ��ˣ�
        for (int i = 1; i < 30; i++)
        {
            sprintf(nameSize, "/normalzombie/moveforwardgif/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    }
    animation->setDelayPerUnit(0.15f);//���ö���֡Ƶ��
    animation->setLoops(-1);//���ò���ѭ�� һֱ���� Ϊ-1
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto animate = Animate::create(animation);
    who->runAction(animate);
}


void coneHeadZombie::dieAndlay(Sprite* who)
{
    auto animation = Animation::create();
    who->stopAllActions();
    char diearray[40] = { 0 };
    /*��ʬ����ſ��*/
    for (int i = 1; i < 11; i++)
    {
        sprintf(diearray, "/normalzombie/die/%d.png", i);
        animation->addSpriteFrameWithFile(diearray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//ֻ����һ��
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim = Animate::create(animation);
    who->runAction(anim);/////////////////////���Ǳ�ɷ���animָ�룿
    
}

//ͷ������
void coneHeadZombie::loseHead(Sprite* who)
{
    auto animation = Animation::create();
    char loseheadarray[40] = { 0 };
    /*��ʬʧȥͷ*/
    for (int i = 1; i < 13; i++)
    {
        sprintf(loseheadarray, "/normalzombie/losehead/%d.png", i);
        animation->addSpriteFrameWithFile(loseheadarray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//ֻ����һ��
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim = Animate::create(animation);
    who->runAction(anim);
}