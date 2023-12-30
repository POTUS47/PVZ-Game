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
    std::string t9t = "/main_menu/chooseminigame.png";
    auto sprite1 = Sprite::create(t9t);
    sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite1->setScale(2.26);
    this->addChild(sprite1, 1);
    
    // ���� Label
    auto label = Label::createWithTTF("Click here Back to Menu", "fonts/Marker Felt.ttf", 34);
    label->setPosition(900,200);
    label->setTextColor(Color4B::BLACK);  // ����������ɫΪ��ɫ
    this->addChild(label,7);
    // ���� Label
    auto label2 = Label::createWithTTF("To Be Continued...", "fonts/Marker Felt.ttf", 96);
    // ���� Label ��λ��
    label2->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    label2->setTextColor(Color4B::BLACK);
    // �� Label ��ӵ�������
    this->addChild(label2,7);


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
    
}


void PromptScene::backtoMain(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}