#include "MiniGame.h"
USING_NS_CC;

Scene* MiniGame::createScene()
{
    return MiniGame::create();
}

bool MiniGame::init()
{

    if (!Scene::init())
    {
        return false;
    }


    //��ȡ��������Χ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //����ͼ
    std::string tt = "/main_menu/chooseminigame.png";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(2.26);
    this->addChild(sprite, 0);

    auto option = MenuItemImage::create(
        "/minigame/option.jpg",
        "/minigame/option.jpg",
        CC_CALLBACK_1(MiniGame::gotoGameCallback, this));
    option->setPosition(Vec2(300, 850));
    option->setScale(0.6);

    auto back = MenuItemImage::create(
        "/minigame/1.png", "/minigame/2.png",
        CC_CALLBACK_1(MiniGame::backtoMain, this)
    );
    back->setPosition(900,200);
    back->setScale(2.0);

    //1.2.�˵� 
    auto menu = Menu::create(option,back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MiniGame::gotoGameCallback(Ref* pSender)
{
    auto level = MiniGameLevel::createWithLevelNumber(1);//��������С��Ϸ��һ��
    Director::getInstance()->replaceScene(level);
}

void MiniGame::backtoMain(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}