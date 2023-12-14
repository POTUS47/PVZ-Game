#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>

USING_NS_CC;

Scene* Level1::createScene()
{
    return Level1::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level1::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //��ȡ��������Χ
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //����Ҫ��-------------------------------------------------------------------------------------
    
    //2.����ͼ
    auto sprite = Sprite::create("/level1/bg.jpg");
    sprite->setPosition(Vec2(visibleSize.width *0.73 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.13);
    this->addChild(sprite, 0);
    // ����MoveBy����
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));

    // ����һ��CallFunc����������ִ�лص�����,����movebyִ����ɺ�ִ��ʲô
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level1::onMoveByFinished, this));

    // ��MoveBy��CallFunc��ϳ�һ�����ж���
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback, nullptr);

    // ���ж���
    sprite->runAction(sequence);
    //-------------test

  


    //-------------------
    return true;
}

// ��������ж���һ����Ա������������MoveBy�������ʱִ�еĻص�
void Level1::onMoveByFinished() {
    // �����ﴦ��MoveBy������ɺ���߼�
    normalZombie b;
    b.generateOne(this);
    normalZombie a;
    Sprite* test = a.generateOne(this);//����һ��ָ����a��ָ��
    a.setIdv(test);
    a.getIdv()->setPosition(1500, 500);
    a.moveForward(a.getIdv());
}




void Level1::goBackMain(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����

    Director::getInstance()->replaceScene(Main_menu::createScene());

}

