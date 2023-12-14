#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include "MarketScene.h"
#include <string>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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

    
    //场景要素-------------------------------------------------------------------------------------
    //1.1.开始游戏按钮---------待改进为进度条显示
    auto startButton = MenuItemImage::create(
                                           "/helloWorld/startbar.png",
                                           "/helloWorld/startbar2.png",
                                           CC_CALLBACK_1(HelloWorld::replaceSceneCallback, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + startButton->getContentSize().height * 2;
    startButton->setPosition(Vec2(x, y));
    startButton->setScale(2.0);

    //1.2.菜单-------------是否可以只用图片按钮？   
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //2.背景图
    std::string tt = "/helloWorld/background.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(1.07);
    this->addChild(sprite, 0);

    //---------------------------test
    //创建一个跑酷的精灵

    auto test = Sprite::create("1.png");

    //设置精灵的坐标

    test->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    test->setScale(2.0);

    //添加到当前层

    this->addChild(test);

    //创建序列帧动画

    auto animation = Animation::create();

    //设置动画名字数组的长度

    char nameSize[30] = { 0 };

    //动画的循环 12张图片

    for (int i = 1; i < 30; i++)

    {

        //循环遍历

        sprintf(nameSize, "%d.png", i);

        //添加到序列帧动画

        animation->addSpriteFrameWithFile(nameSize);

    }

    //设置动画帧的时间间隔

    animation->setDelayPerUnit(0.03f);

    //设置播放循环 一直播放 为-1

    animation->setLoops(-1);

    //设置动画结束后恢复到第一帧

    animation->setRestoreOriginalFrame(true);

    //创建动画动作

    auto animate = Animate::create(animation);

    //播放动画

    test->runAction(animate);
    auto moveBy = MoveBy::create(5, Vec2(0, -1000));
    test->runAction(moveBy);




    return true;
}




void HelloWorld::replaceSceneCallback(Ref* pSender)
{
    //按下开始游戏后转入菜单场景
    
    Director::getInstance()->replaceScene(Main_menu::createScene());
    
}

