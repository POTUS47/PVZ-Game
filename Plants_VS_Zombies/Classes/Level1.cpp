#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //����Ҫ��-------------------------------------------------------------------------------------
    
    //2.����ͼ
    auto sprite = Sprite::create("/level1/bg.jpg");
    sprite->setPosition(Vec2(visibleSize.width *0.73 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.13);
    this->addChild(sprite, 0);
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    sprite->runAction(moveBy);

    zombie::test();

    return true;
}




void Level1::goBackMain(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����

    Director::getInstance()->replaceScene(Main_menu::createScene());

}

