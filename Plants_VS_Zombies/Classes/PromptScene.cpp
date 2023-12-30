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
    this->addChild(sprite, 1);

    auto back = MenuItemImage::create(
        "/minigame/1.png", "/minigame/2.png",
        CC_CALLBACK_1(PromptScene::backtoMain, this)
    );
    back->setPosition(900, 200);
    back->setScale(2.0);

    // ���� Label
    auto label = Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 24);
    // ���� Label ��λ��
    label->setPosition(900,200);
    // �� Label ��ӵ�������
    this->addChild(label);

    // ��Ӵ����¼�������
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // ���ô����¼��ص�����
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // �ڵ�� Label ������ʱִ�з������˵��Ĳ���
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // �������¼���������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);

    return true;
    // ���� Label
    auto label2 = Label::createWithTTF("To Be Continued...", "fonts/Marker Felt.ttf", 24);
    // ���� Label ��λ��
    label2->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    // �� Label ��ӵ�������
    this->addChild(label2);

    //1.2.�˵� 
    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


void PromptScene::backtoMain(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}