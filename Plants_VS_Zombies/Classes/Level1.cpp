#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
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

    //获取可视区域范围
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //场景要素-------------------------------------------------------------------------------------
    
    //2.背景图
    auto sprite = Sprite::create("/level1/bg.jpg");
    sprite->setPosition(Vec2(visibleSize.width *0.73 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.13);
    this->addChild(sprite, 0);
    // 创建MoveBy动作
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));

    // 创建一个CallFunc动作，用于执行回调函数,即在moveby执行完成后执行什么
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level1::onMoveByFinished, this));

    // 将MoveBy和CallFunc组合成一个序列动作
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback, nullptr);

    // 运行动作
    sprite->runAction(sequence);
    //-------------test

  


    //-------------------
    return true;
}

// 在你的类中定义一个成员函数，用于在MoveBy动作完成时执行的回调
void Level1::onMoveByFinished() {
    // 在这里处理MoveBy动作完成后的逻辑
    normalZombie b;
    b.generateOne(this);
    normalZombie a;
    Sprite* test = a.generateOne(this);//返回一个指向精灵a的指针
    a.setIdv(test);
    a.getIdv()->setPosition(1500, 500);
    a.moveForward(a.getIdv());
}




void Level1::goBackMain(Ref* pSender)
{
    //按下开始游戏后转入菜单场景

    Director::getInstance()->replaceScene(Main_menu::createScene());

}

