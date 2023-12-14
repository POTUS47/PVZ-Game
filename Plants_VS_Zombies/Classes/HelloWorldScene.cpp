#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include "MarketScene.h"
#include <string>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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

    
    //����Ҫ��-------------------------------------------------------------------------------------
    //1.1.��ʼ��Ϸ��ť---------���Ľ�Ϊ��������ʾ
    auto startButton = MenuItemImage::create(
                                           "/helloWorld/startbar.png",
                                           "/helloWorld/startbar2.png",
                                           CC_CALLBACK_1(HelloWorld::replaceSceneCallback, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + startButton->getContentSize().height * 2;
    startButton->setPosition(Vec2(x, y));
    startButton->setScale(2.0);

    //1.2.�˵�-------------�Ƿ����ֻ��ͼƬ��ť��   
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //2.����ͼ
    std::string tt = "/helloWorld/background.jpg";
    auto sprite = Sprite::create(tt);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(1.07);
    this->addChild(sprite, 0);

    //---------------------------test
    //����һ���ܿ�ľ���

    auto test = Sprite::create("1.png");

    //���þ��������

    test->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    test->setScale(2.0);

    //��ӵ���ǰ��

    this->addChild(test);

    //��������֡����

    auto animation = Animation::create();

    //���ö�����������ĳ���

    char nameSize[30] = { 0 };

    //������ѭ�� 12��ͼƬ

    for (int i = 1; i < 30; i++)

    {

        //ѭ������

        sprintf(nameSize, "%d.png", i);

        //��ӵ�����֡����

        animation->addSpriteFrameWithFile(nameSize);

    }

    //���ö���֡��ʱ����

    animation->setDelayPerUnit(0.03f);

    //���ò���ѭ�� һֱ���� Ϊ-1

    animation->setLoops(-1);

    //���ö���������ָ�����һ֡

    animation->setRestoreOriginalFrame(true);

    //������������

    auto animate = Animate::create(animation);

    //���Ŷ���

    test->runAction(animate);
    auto moveBy = MoveBy::create(5, Vec2(0, -1000));
    test->runAction(moveBy);




    return true;
}




void HelloWorld::replaceSceneCallback(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    
    Director::getInstance()->replaceScene(Main_menu::createScene());
    
}

