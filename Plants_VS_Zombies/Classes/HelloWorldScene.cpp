#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    
    //获取可视区域范围
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    //场景要素
    //1.1.开始游戏按钮---------待改进为进度条显示
    auto startButton = MenuItemImage::create(
                                           "/helloWorld/startbar.png",
                                           "/helloWorld/startbar2.png",
                                           CC_CALLBACK_1(HelloWorld::replaceSceneCallback, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + startButton->getContentSize().height * 2;
    startButton->setPosition(Vec2(x, y));
    startButton->setScale(2.0);

    //1.2.菜单 
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //2.背景图
    std::string tt = "/helloWorld/background.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(1.07);
    this->addChild(sprite, 0);

}


void HelloWorld::replaceSceneCallback(Ref* pSender)
{
    //按下开始游戏后转入菜单场景
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

