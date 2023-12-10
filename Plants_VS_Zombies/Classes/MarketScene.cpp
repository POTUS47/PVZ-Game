#include "SimpleAudioEngine.h"
#include "MarketScene.h"

USING_NS_CC;

Scene* Market::createScene()
{
    return Market::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Market::init()
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
    //����
    auto sprite = Sprite::create("/market/dave.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        sprite->setScale(1.07);
        this->addChild(sprite, 0);
    }
    //---------------------------------------------------------------------------------
    
    return true;
}


void Market::replaceSceneCallback(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Market::createScene());
}
