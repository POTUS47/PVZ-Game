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

    auto closeItem = MenuItemImage::create(
        "/minigame/1.png",
        "/minigame/2.png",
        CC_CALLBACK_1(MiniGame::gotoMenu, this));//////////////////////����޷�Ӧ������������
    float x = 333;
    float y = 333;///////////////////////////////////////�޸�λ��
    closeItem->setPosition(Vec2(x, y));
    closeItem->setScale(2);
    this->addChild(closeItem, 2);

    Label* label = Label::createWithTTF("back", "fonts/arial.ttf", 34);

    // ����Label��λ��
    label->setPosition(Vec2(x, y));

    // ��Label��ӵ�������
    this->addChild(label, 3);

        return true;
}
void MiniGame::gotoMenu(Ref* pSender)
{
    //ת��˵�����
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

