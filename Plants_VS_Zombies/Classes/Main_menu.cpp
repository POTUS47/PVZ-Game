#include "Main_menu.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MarketScene.h"
#include "Level.h"
#include "MiniGame.h"
#include"achievement.h"
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
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/menu.mp3");

    // ���ű�������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/menu.mp3", true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //1��������ť
    auto closeItem = MenuItemImage::create(
        "quit.png",
        "quit.png",
        CC_CALLBACK_1(Main_menu::menuCloseCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = visibleSize.width*0.9;
        float y = visibleSize.height * 0.15;
        closeItem->setPosition(Vec2(x, y));
        closeItem->setScale(2.5);
    }

   
    
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
        "/main_menu/adventure2.png", CC_CALLBACK_1(Main_menu::startGameCallback, this)
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
        CC_CALLBACK_1(Main_menu::gotoMiniGame, this)
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

    float x1 = origin.x + visibleSize.width / 3 * 2;
    float y1 = origin.y + visibleSize.height / 4 - 50;
    market->setPosition(Vec2(x1, y1));
    market->setScale(2.5);
//5.�ɾͰ�ť
    auto achievement = MenuItemImage::create(
        "/main_menu/1.png", "/main_menu/2.png",
        CC_CALLBACK_1(Main_menu::gotoAchievement, this)
    );////////////////////////////�˴���Ҫ����һ�������̵곡���ĺ������ǵ��޸İ�ťͼƬ

    float x = origin.x + visibleSize.width / 4;
    float y = origin.y + visibleSize.height / 4*1.2 ;///////////////////////
    achievement->setPosition(Vec2(x, y));
    achievement->setScale(2.65);

    //�����˵�
    auto menu = Menu::create(adventure_mode, mini_game_mode, market, closeItem, achievement,NULL);
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


void Main_menu::startGameCallback(Ref* pSender)
{
    // ��ȡ���¹ؿ����ȣ��������ʹ��UserDefault�����˹ؿ�����
    int latestLevel = GameDataManager::getLevelProgress();
    if (latestLevel > 2) {
        GameDataManager::saveLevelProgress(1);//���浱ǰ�ؿ�����Ϊ1
        Director::getInstance()->replaceScene(PromptScene::createScene());
        return;
    }
    // �����Ӧ��������Ϸ����
    auto level = Level::createWithLevelNumber(latestLevel);
    // �� Level ������ӵ�������
    Director::getInstance()->replaceScene(level);

}

void Main_menu::gotoMarket(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��˵�����
    Director::getInstance()->replaceScene(Market::createScene());
}


void Main_menu::gotoMiniGame(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת�����˵�����
    Director::getInstance()->replaceScene(MiniGame::createScene());
}

void Main_menu::gotoAchievement(Ref* pSender)
{
    //���¿�ʼ��Ϸ��ת��ɾͳ���
    Director::getInstance()->replaceScene(AchievementScene::createScene());
}