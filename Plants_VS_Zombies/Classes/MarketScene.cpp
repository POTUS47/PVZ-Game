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

    //获取可视区域范围
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //场景要素-------------------------------------------------------------------------------------
    //戴夫
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
    //按下开始游戏后转入菜单场景
    Director::getInstance()->replaceScene(Market::createScene());
}
