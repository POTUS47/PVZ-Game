#include "achievement.h"
#include"User.h"
#include<string>
USING_NS_CC;

Scene* AchievementScene::createScene()
{
    return AchievementScene::create();
}

bool AchievementScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //获取可视区域范围
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取可视区域原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //背景图
    std::string t9t = "/main_menu/chooseminigame.png";
    auto sprite1 = Sprite::create(t9t);
    sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite1->setScale(2.26);
    this->addChild(sprite1, 1);

    // 创建 Label
    auto label = Label::createWithTTF("Click here Back to Menu", "fonts/Marker Felt.ttf", 74);
    label->setPosition(900, 200);
    label->setTextColor(Color4B::BLACK);  // 设置字体颜色为黑色
    this->addChild(label, 7);

    //当前关卡进度///////////////////////////////////////////不知道为啥显示不出来
    int latestLevel = GameDataManager::getLevelProgress();
    std::string s = "游戏进行至第" + std::to_string(latestLevel) + "关";
    auto label2 = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 54);
    label2->setPosition(1100, 800);
    label2->setTextColor(Color4B::BLACK);  // 设置字体颜色为黑色
    this->addChild(label2, 8);

    //配图
    auto sprite2 = Sprite::create("/main_menu/3.png");
    sprite2->setPosition(400,800);
    sprite2->setScale(0.2);
    this->addChild(sprite2, 1);

    // 添加触摸事件监听器
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // 设置触摸事件回调函数
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // 在点击 Label 区域内时执行返回主菜单的操作
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // 将触摸事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);
    return true;

}


void AchievementScene::backtoMain(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}