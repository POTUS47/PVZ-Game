#include "MiniGame.h"
USING_NS_CC;

Scene* MiniGame::createScene()
{
    return MiniGame::create();
}

// CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

bool MiniGame::init()
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
    std::string tt = "/main_menu/chooseminigame.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.26);
    this->addChild(sprite, 0);

    auto closeItem = MenuItemImage::create(
        "/minigame/1.png",
        "/minigame/2.png",
        CC_CALLBACK_1(MiniGame::gotoMenu, this));//////////////////////点击无反应？？？？？？
    float x = 333;
    float y = 333;///////////////////////////////////////修改位置
    closeItem->setPosition(Vec2(x, y));
    closeItem->setScale(2);
    this->addChild(closeItem, 2);

    Label* label = Label::createWithTTF("back", "fonts/arial.ttf", 34);

    // 设置Label的位置
    label->setPosition(Vec2(x, y));

    // 将Label添加到场景中
    this->addChild(label, 3);

        return true;
}
void MiniGame::gotoMenu(Ref* pSender)
{
    //转入菜单场景
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

