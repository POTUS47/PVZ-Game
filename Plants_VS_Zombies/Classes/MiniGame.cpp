#include "MiniGame.h"
USING_NS_CC;

Scene* MiniGame::createScene()
{
    return MiniGame::create();
}

void MiniGame::onExit() {
    // 停止BGM
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

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

    return true;
}


