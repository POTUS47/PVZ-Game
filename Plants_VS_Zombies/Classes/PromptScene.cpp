#include "PromptScene.h"
USING_NS_CC;

Scene* PromptScene::createScene()
{
    return PromptScene::create();
}

bool PromptScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/mini.mp3");

    // 播放背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/mini.mp3", true);

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
    auto label = Label::createWithTTF("Click here Back to Menu", "fonts/Marker Felt.ttf", 34);
    label->setPosition(900,200);
    label->setTextColor(Color4B::BLACK);  // 设置字体颜色为黑色
    this->addChild(label,7);
    // 创建 Label
    auto label2 = Label::createWithTTF("To Be Continued...", "fonts/Marker Felt.ttf", 96);
    // 设置 Label 的位置
    label2->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    label2->setTextColor(Color4B::BLACK);
    // 将 Label 添加到场景中
    this->addChild(label2,7);


    // 添加触摸事件监听器
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // 设置触摸事件回调函数
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // 在点击 Label 区域内时执行返回主菜单的操作
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // 将触摸事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);
    return true;
    
}


void PromptScene::backtoMain(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}