#include "Main_menu.h"
#include "SimpleAudioEngine.h"
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
    ////////�޸����˵������ͼƬ
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
        "/main_menu/adventure2.png", CC_CALLBACK_1(Main_menu::menuCloseCallback, this)
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
        float x = origin.x + visibleSize.width /2*3;
        float y = origin.y + visibleSize.height / 2;
        adventure_mode->setPosition(Vec2(x, y));
        ////////////�޸�ð��ģʽ��ť�����λ��
    }
    auto menu1 = Menu::create(adventure_mode, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    //3.����С��Ϸ��ť
   /* auto mini_game_mode = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [](cocos2d::Ref* sender) {
            auto mini_game_menu = mini_game_menu::create();
            cocos2d::Director::getInstance()->replaceScene(mini_game_menu);
        }
        );////////////////�˴���Ҫ����һ������С��Ϸģʽ�����ĺ������ǵ��޸İ�ťͼƬ

    if (mini_game_mode == nullptr ||
        mini_game_mode->getContentSize().width <= 0 ||
        mini_game_mode->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        mini_game_mode->setPosition(Vec2(x, y));
        ////////////�޸�С��Ϸģʽ��ť�����λ��
    }
    */
    //4.�̵갴ť
    /*auto market = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [](cocos2d::Ref* sender) {
            auto Market = Market::create();
            cocos2d::Director::getInstance()->replaceScene(Market);
        }
        );////////////////////////////�˴���Ҫ����һ�������̵곡���ĺ������ǵ��޸İ�ťͼƬ

    if (market == nullptr ||
        market->getContentSize().width <= 0 ||
        market->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        market->setPosition(Vec2(x, y));
        ////////////�޸�С��Ϸģʽ��ť�����λ��
    }
    */

    // ��ť�ص�����
    /*void startGameCallback(Ref * pSender)
    {
        // ��ȡ���¹ؿ����ȣ��������ʹ��UserDefault�����˹ؿ�����
        int latestLevel = UserDefault::getInstance()->getIntegerForKey("LatestLevel", 1);

        // ������Ӧ����Ϸ����
        auto gameScene = GameScene::createScene(latestLevel);

        // �л�����
        Director::getInstance()->replaceScene(gameScene);
    }
    return true;
    */
}

//�˵���ť1��������ť�Ļص�����
void Main_menu::menuCloseCallback(Ref* pSender)
{
    //�˳���Ϸ
    Director::getInstance()->end();
}
//������ť�Ļص�������û�е�������������ֱ������������Ƕ�׵���creat�Ĳ����б��С�
