#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>
#include<vector>
#include"God.h"

extern std::vector<Zombie*>waiting;

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
    srand(static_cast<unsigned>(time(0)));
    if (!Scene::init())
    {
        return false;
    }
    god = new God();
    //获取可视区域范围
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //场景要素-------------------------------------------------------------------------------------
    
    //背景图
    auto sprite = Sprite::create("/level1/bg.jpg");
    sprite->setPosition(Vec2(visibleSize.width *0.73 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.47,2.13);
    this->addChild(sprite, 0);
    background = sprite;


    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);

    // 创建一个CallFunc动作，用于执行回调函数,即在moveby执行完成后执行什么
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level1::onMoveByFinished, this));
    auto moveTotheRight = CallFunc::create(CC_CALLBACK_0(Level1::moveRight, this));
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback,moveTotheRight, nullptr);
    sprite->runAction(sequence);
    

    //-------------test
    //this->scheduleOnce(schedule_selector(Level1::update), 5.0f);
  
    return true;
}

// 在你的类中定义一个成员函数，用于在MoveBy动作完成时执行的回调
void Level1::onMoveByFinished() 
{
    god->updateZombies(1, this);
}


void Level1::update(float dt)
{
    god->updateZombies(1,this);
}



//按下开始游戏后转入菜单场景
void Level1::goBackMain(Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

void Level1::moveLeft()
{
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);
}

void Level1::moveRight()
{
    
    // 创建按钮
    /*auto closeButton = MenuItemImage::create(
        "close_button_normal.png",
        "close_button_selected.png",
        this->removeFromParentAndCleanup(true));

    closeButton->setPosition(300,500);

    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    transparentLayer->addChild(menu);*/
    int a = 0;
    //弹出选择开始按钮，按下再moveBy
    while (a == 0) {

    }
    auto moveBack = MoveBy::create(2, Vec2(620, 0));

    // 移动场景
    background->runAction(moveBack->clone());

    // 移动每个僵尸
    for (int i = 0; i < waiting.size(); i++) {
        (waiting[i]->getIdv())->runAction(moveBack->clone());
    }
}

