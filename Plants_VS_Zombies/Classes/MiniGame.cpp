#include "MiniGame.h"
USING_NS_CC;

Scene* MiniGame::createScene()
{
    return MiniGame::create();
}

void MiniGame::onExit() {
    // ֹͣBGM
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

bool MiniGame::init()
{

    if (!Scene::init())
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/mini.mp3");

    // ���ű�������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/mini.mp3", true);

    //��ȡ��������Χ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //����ͼ
    std::string tt = "/main_menu/chooseminigame.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.26);
    this->addChild(sprite, 0);

    return true;
}


