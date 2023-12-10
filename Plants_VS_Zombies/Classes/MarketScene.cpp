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

    //获取可视区域范围
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //场景要素-------------------------------------------------------------------------------------
    //戴夫
    auto sprite = Sprite::create("/market/dave.png");
   
        sprite->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height/3+  origin.y));
        sprite->setScale(2.5);
        this->addChild(sprite, 0);
 
    //---------------------------------------------------------------------------------
    //返回菜单的按钮

    return true;
}


void Market::replaceSceneCallback(Ref* pSender)
{
    //按下开始游戏后转入菜单场景
    Director::getInstance()->replaceScene(Market::createScene());
}
