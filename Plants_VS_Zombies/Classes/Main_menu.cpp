#include "Main_menu.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MarketScene.h"
#include "Level1.h"
//ͼƬ����3:2
///////����б���������޸ĵ���˼
USING_NS_CC;

Scene* Main_menu::createScene()
{
    return Main_menu::create();
}
// ������Ϣ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Main_menuScene.cpp\n");
}


bool Main_menu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //1��������ť
   /* auto closeItem = MenuItemImage::create(
        "zombietest.png",
        "zombietest.png",
        CC_CALLBACK_1(Main_menu::menuCloseCallback, this));
    ////////////////�޸��˳���ťͼƬ
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        ////////////�޸��˳���ť�����λ��
    }
    //���ڵ�һ���˳���ť�����Ǵ����˵�menu
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    */
    // ���������ͼƬ���Ծ�����ʽ��
    auto sprite = Sprite::create("/main_menu/background.png");
    if (sprite == nullptr)
    {
        problemLoading("'Main_menu.png'");
    }
    else
    {
        //�Ѿ���������м�
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //�Ѿ�����Ϊ���������layer��
        sprite->setScale(2.3);
        this->addChild(sprite, 0);///////����ԽСԽ�ȱ���Ⱦ��ע������˳�����0
    }

    //2.ð��ģʽ��ť
    auto adventure_mode = MenuItemImage::create(
        "/main_menu/adventure1.png",
        "/main_menu/adventure2.png", CC_CALLBACK_1(Main_menu::gotoLevel1, this)
        );////////////////////////////�˴���Ҫ����һ������ð��ģʽ���¹ؿ��ĺ������ǵ��޸İ�ťͼƬ
    ///////���Ǽٶ�ʹ����UserDefault::getInstance()->setIntegerForKey("LatestLevel", 5);��ʽ�洢����
    if (adventure_mode == nullptr ||
        adventure_mode->getContentSize().width <= 0 ||
        adventure_mode->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width /4*3-100;
        float y = origin.y + visibleSize.height / 4*3+50;
        adventure_mode->setPosition(Vec2(x, y));
        adventure_mode->setScale(2.0);
        ////////////�޸�ð��ģʽ��ť�����λ��
    }
    

    //3.����С��Ϸ��ť
   
    auto mini_game_mode = MenuItemImage::create(
        "/main_menu/minigame1.png",
        "/main_menu/minigame2.png",
        CC_CALLBACK_1(Main_menu::menuCloseCallback, this)
        );////////////////�˴���Ҫ����һ������С��Ϸģʽ�����ĺ���

    if (mini_game_mode == nullptr ||
        mini_game_mode->getContentSize().width <= 0 ||
        mini_game_mode->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width /4*3-100;
        float y = origin.y + visibleSize.height / 5*3;
        mini_game_mode->setPosition(Vec2(x, y));
        mini_game_mode->setScale(2.0);
    }
 
    
    //4.�̵갴ť
    auto market = MenuItemImage::create(
        "/main_menu/shopbutton1.png", "/main_menu/shopbutton2.png",
        CC_CALLBACK_1(Main_menu::gotoMarket, this)
        );////////////////////////////�˴���Ҫ����һ�������̵곡���ĺ������ǵ��޸İ�ťͼƬ

        float x = origin.x + visibleSize.width / 3*2;
        float y = origin.y + visibleSize.height / 4-50;
        market->setPosition(Vec2(x, y));
        market->setScale(2.5);
 


        auto menu = Menu::create(adventure_mode, mini_game_mode,market, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 0);

        return true;
}

//�˵���ť1��������ť�Ļص�����
void Main_menu::menuCloseCallback(Ref* pSender)
{
    //�˳���Ϸ
    Director::getInstance()->end();
}
//������ť�Ļص�������û�е�������������ֱ������������Ƕ�׵���creat�Ĳ����б��С�

//
void Main_menu::startGameCallback(Ref* pSender)
{
    // ��ȡ���¹ؿ����ȣ��������ʹ��UserDefault�����˹ؿ�����
    int latestLevel = UserDefault::getInstance()->getIntegerForKey("LatestLevel", 1);

    // �����Ӧ��������Ϸ����
    GoToWhichScene(latestLevel);

}

void Main_menu::GoToWhichScene(int latestLevel) {
    switch (latestLevel) {
        case 1: {
            Scene* aaa = Level1::createScene();
            Director::getInstance()->replaceScene(aaa);
            break;
        }
    case 2:

    default:
            break;
    }
}


void Main_menu::gotoMarket(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Market::createScene());
}

void Main_menu::gotoLevel1(Ref* pSender)
{
    Director::getInstance()->replaceScene(Level1::createScene());
}