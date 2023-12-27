#include"NormalZombie.h"
USING_NS_CC;

//��ͨ��ʬ�Ĺ��캯��
//������ʼλ�� ���Ŵ�С
normalZombie::normalZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(30);
    setWeapen(false);//��ͨ��ʬû������
    setCondition(WAIT);
    setHP(100);
    setAttack(2);
    setEatingTime(1.0f);
    auto normalzombie = cocos2d::Sprite::create("/normalzombie/standgif/1.png");
    normalzombie->setPosition(x, y);
    normalzombie->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(normalzombie, 2);
    setIdv(normalzombie);//������ָ�����idv
}

void normalZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void normalZombie::healthyEating(Sprite* who) 
{
    who->stopAllActions();
    auto animation = Animation::create();
    char healthyattackarray[40] = { 0 };
    /*��ʬ��ֲ��*/
    for (int i = 1; i < 22; i++)
    {
        sprintf(healthyattackarray, "/normalzombie/healthyattack/%d.png", i);
        animation->addSpriteFrameWithFile(healthyattackarray);
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
void normalZombie::moveForward(Sprite* who)
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
    /*��·ǰ��gif*/
    for (int i = 1; i < 30; i++)
    {
        sprintf(nameSize, "/normalzombie/moveforwardgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);//���ö���֡Ƶ��
    animation->setLoops(-1);//���ò���ѭ�� һֱ���� Ϊ-1
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto animate = Animate::create(animation);
    who->runAction(animate);
}


void normalZombie::moveWithoutArm(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize1[40] = { 0 };
    /*�ϸ첲��ǰ��*/
    for (int i = 1; i < 21; i++)
    {
        sprintf(nameSize1, "/normalzombie/standgif/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize1);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim2 = Animate::create(animation);
}




void normalZombie::dieAndlay(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
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
    who->runAction(anim);
    

}




//ͷ������
void normalZombie::loseHead(Sprite* who)
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

