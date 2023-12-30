#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    
    //��ȡ��������Χ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    //����Ҫ��
    //1.1.��ʼ��Ϸ��ť---------���Ľ�Ϊ��������ʾ
    auto startButton = MenuItemImage::create(
                                           "/helloWorld/startbar.png",
                                           "/helloWorld/startbar2.png",
                                           CC_CALLBACK_1(HelloWorld::replaceSceneCallback, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + startButton->getContentSize().height * 2;
    startButton->setPosition(Vec2(x, y));
    startButton->setScale(2.0);

    //1.2.�˵� 
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //2.����ͼ
    std::string tt = "/helloWorld/background.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(1.07);
    this->addChild(sprite, 0);

}


void HelloWorld::replaceSceneCallback(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

