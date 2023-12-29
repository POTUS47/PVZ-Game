#include "SimpleAudioEngine.h"
#include "MarketScene.h"
#include "Main_menu.h"

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
    // ����
    auto background = Sprite::create("/market/background.jpg");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    background->setScale(2.1);
    this->addChild(background, -1);
    //---------------------------------------------------------------------------------------------
    //����
    auto sprite = Sprite::create("/market/dave.png");
   
        sprite->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height/3+  origin.y));
        sprite->setScale(2.5);
        this->addChild(sprite, 0);
 
    //---------------------------------------------------------------------------------
    //���ز˵��İ�ť
        auto back = MenuItemImage::create(
            "/market/backbutton1.png", "/market/backbutton2.png",
            CC_CALLBACK_1(Market::goBackMain, this)
        );////////////////////////////�˴���Ҫ����һ�������̵곡���ĺ������ǵ��޸İ�ťͼƬ

        float x = origin.x + visibleSize.width *0.55;
        float y = origin.y + visibleSize.height *0.2;
        back->setPosition(Vec2(x, y));
        back->setScale(2.0);



        auto menu = Menu::create(back, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 0);
    //----------------------------------------------------------------------------------------
    //��

        auto car = Sprite::create("/market/caropen.jpg");
        car->setPosition(visibleSize.width *0.65, visibleSize.height *0.45);
        car->setScale(2.4);
        this->addChild(car, -1);
    //------------------------------------------------------------------------------------
    //���ϱ�־
        auto sign = Sprite::create("/market/sign.png");
        sign->setPosition(visibleSize.width * 0.65, visibleSize.height * 0.89);
        sign->setScale(2.3);
        this->addChild(sign, -1);

    return true;
}


void Market::goBackMain(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Main_menu::createScene());
}
