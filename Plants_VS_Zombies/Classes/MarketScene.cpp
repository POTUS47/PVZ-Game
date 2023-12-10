#include "SimpleAudioEngine.h"
#include "MarketScene.h"

USING_NS_CC;

Scene* Market::createScene()
{
    return Market::create();
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
   
        sprite->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height/3+  origin.y));
        sprite->setScale(2.5);
        this->addChild(sprite, 0);
 
    //---------------------------------------------------------------------------------
    //���ز˵��İ�ť

    return true;
}


void Market::replaceSceneCallback(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Market::createScene());
}
