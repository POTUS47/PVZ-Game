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

    //获取可视区域范围
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //场景要素-------------------------------------------------------------------------------------
    // 背景
    auto background = Sprite::create("/market/background.jpg");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    background->setScale(2.1);
    this->addChild(background, -1);
    //---------------------------------------------------------------------------------------------
    //戴夫
    auto sprite = Sprite::create("/market/dave.png");
   
        sprite->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height/3+  origin.y));
        sprite->setScale(2.5);
        this->addChild(sprite, 0);
 
    //---------------------------------------------------------------------------------
    //返回菜单的按钮
        auto back = MenuItemImage::create(
            "/market/backbutton1.png", "/market/backbutton2.png",
            CC_CALLBACK_1(Market::goBackMain, this)
        );////////////////////////////此处需要调用一个进入商店场景的函数，记得修改按钮图片

        float x = origin.x + visibleSize.width *0.55;
        float y = origin.y + visibleSize.height *0.2;
        back->setPosition(Vec2(x, y));
        back->setScale(2.0);



        auto menu = Menu::create(back, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 0);
    //----------------------------------------------------------------------------------------
    //车

        auto car = Sprite::create("/market/caropen.jpg");
        car->setPosition(visibleSize.width *0.65, visibleSize.height *0.45);
        car->setScale(2.4);
        this->addChild(car, -1);
    //------------------------------------------------------------------------------------
    //车上标志
        auto sign = Sprite::create("/market/sign.png");
        sign->setPosition(visibleSize.width * 0.65, visibleSize.height * 0.89);
        sign->setScale(2.3);
        this->addChild(sign, -1);

    return true;
}


void Market::goBackMain(Ref* pSender)
{
    //按下开始游戏后转入菜单场景
    Director::getInstance()->replaceScene(Main_menu::createScene());
}
