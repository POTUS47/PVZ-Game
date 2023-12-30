#include"NewspaperZombie.h"
USING_NS_CC;

//��ֽ��ʬ�Ĺ��캯��
//������ʼλ�� ���Ŵ�С
newspaperZombie::newspaperZombie(int x, int y, double scale, Scene* scene)
{
    setSpeed(30);
    setWeapen(true);//�б�ֽ
    setCondition(WAIT);
    setHP(80);
    setAttack(10);
    setEatingTime(1.2f);
    auto normalzombie = cocos2d::Sprite::create("/newspaperzombie/wait/1.png");
    normalzombie->setPosition(x, y);
    normalzombie->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(normalzombie, 2);
    setIdv(normalzombie);//������ָ�����idv
}

void newspaperZombie::standBy(Sprite* who)
{
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 20; i++)
    {
        sprintf(nameSize, "/newspaperzombie/wait/%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
    who->runAction(animate);
}

void newspaperZombie::healthyEating(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();

    char healthyattackarray[50] = { 0 };
    if (getWeapen() == true) {//������ڻ�������
        for (int i = 1; i < 9; i++)
        {
            sprintf(healthyattackarray, "/newspaperzombie/paperattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
    }
    else {//���û�����ˣ�ñ�ӵ��ˣ�
        for (int i = 1; i < 8; i++)
        {
            sprintf(healthyattackarray, "/newspaperzombie/withoutpaperattack/%d.png", i);
            animation->addSpriteFrameWithFile(healthyattackarray);
        }
        setEatingTime(0.7f);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);//ѭ������
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim = Animate::create(animation);
    who->runAction(anim);
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BGM/newspaper.mp3");
}

/**
* @param �������ĸ�����Ҫ��ǰ��
* @return void
*/
void newspaperZombie::moveForward(Sprite* who)
{
    if (getCondition() == WAIT) {//����Ǵӵȴ�����Ϊ��ǰ��
        int starty = getCol();
        who->setPosition(1950, starty * 200 - 10);//��Ҫ���ó���λ��
    }
    setCondition(WALKING);
    who->stopAllActions();
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    if (getWeapen() == true) {//������ڻ�������
        for (int i = 1; i < 20; i++)
        {
            sprintf(nameSize, "/newspaperzombie/paperwalk/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
        auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
        who->runAction(moveBy);
    }
    else {//���û�����ˣ�ñ�ӵ��ˣ�
        for (int i = 1; i < 15; i++)
        {
            sprintf(nameSize, "/newspaperzombie/withoutpaperwalk/%d.png", i);
            animation->addSpriteFrameWithFile(nameSize);
        }
        setSpeed(70);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BGM/newspaper.mp3");
        auto moveBy = MoveBy::create(2100 / this->getSpeed(), Vec2(-2100, 0));
        who->runAction(moveBy);
    }
    animation->setDelayPerUnit(0.1f);//���ö���֡Ƶ��
    animation->setLoops(-1);//���ò���ѭ�� һֱ���� Ϊ-1
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto animate = Animate::create(animation);
    who->runAction(animate);
   
}

void newspaperZombie::dieAndlay(Sprite* who)
{
    who->stopAllActions();
    auto animation = Animation::create();
    char diearray[40] = { 0 };
    /*��ʬ����ſ��*/
    for (int i = 1; i < 12; i++)
    {
        sprintf(diearray, "/newspaperzombie/die/%d.png", i);
        animation->addSpriteFrameWithFile(diearray);
    }
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(1);//ֻ����һ��
    animation->setRestoreOriginalFrame(true);//����������ָ�����һ֡
    auto anim = Animate::create(animation);
    who->runAction(anim);


}




//ͷ������
void newspaperZombie::loseHead(Sprite* who)
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

