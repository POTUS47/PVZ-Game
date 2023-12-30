#include "Main_menu.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MarketScene.h"
#include "Level.h"
#include "MiniGame.h"
#include"achievement.h"
//图片比例3:2
///////多条斜线是提醒修改的意思
USING_NS_CC;

Scene* Main_menu::createScene()
{
    return Main_menu::create();
}
// 报错信息输出
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

    // 播放背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/menu.mp3", true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //1：结束按钮
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

   
    
    // 添加主界面图片（以精灵形式）
    auto sprite = Sprite::create("/main_menu/background.png");
    if (sprite == nullptr)
    {
        problemLoading("'Main_menu.png'");
    }
    else
    {
        //把精灵放在正中间
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //把精灵作为孩子添加至layer中
        sprite->setScale(2.3);
        this->addChild(sprite, 0);///////数字越小越先被渲染。注意后面的顺序大于0
    }

    //2.冒险模式按钮
    auto adventure_mode = MenuItemImage::create(
        "/main_menu/adventure1.png",
        "/main_menu/adventure2.png", CC_CALLBACK_1(Main_menu::startGameCallback, this)
        );////////////////////////////此处需要调用一个进入冒险模式最新关卡的函数，记得修改按钮图片
    ///////我们假定使用了UserDefault::getInstance()->setIntegerForKey("LatestLevel", 5);形式存储进度
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
        ////////////修改冒险模式按钮的相对位置
    }
    

    //3.玩玩小游戏按钮
   
    auto mini_game_mode = MenuItemImage::create(
        "/main_menu/minigame1.png",
        "/main_menu/minigame2.png",
        CC_CALLBACK_1(Main_menu::gotoMiniGame, this)
        );////////////////此处需要调用一个进入小游戏模式场景的函数

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

    //4.商店按钮
    auto market = MenuItemImage::create(
        "/main_menu/shopbutton1.png", "/main_menu/shopbutton2.png",
        CC_CALLBACK_1(Main_menu::gotoMarket, this)
    );////////////////////////////此处需要调用一个进入商店场景的函数，记得修改按钮图片

    float x1 = origin.x + visibleSize.width / 3 * 2;
    float y1 = origin.y + visibleSize.height / 4 - 50;
    market->setPosition(Vec2(x1, y1));
    market->setScale(2.5);
//5.成就按钮
    auto achievement = MenuItemImage::create(
        "/main_menu/1.png", "/main_menu/2.png",
        CC_CALLBACK_1(Main_menu::gotoAchievement, this)
    );////////////////////////////此处需要调用一个进入商店场景的函数，记得修改按钮图片

    float x = origin.x + visibleSize.width / 4;
    float y = origin.y + visibleSize.height / 4*1.2 ;///////////////////////
    achievement->setPosition(Vec2(x, y));
    achievement->setScale(2.65);

    //创建菜单
    auto menu = Menu::create(adventure_mode, mini_game_mode, market, closeItem, achievement,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

    return true;
 
}

//菜单按钮1：结束按钮的回调函数
void Main_menu::menuCloseCallback(Ref* pSender)
{
    //退出游戏
    Director::getInstance()->end();
}
//其他按钮的回调函数并没有单独给出，而是直接用匿名函数嵌套到了creat的参数列表中。


void Main_menu::startGameCallback(Ref* pSender)
{
    // 获取最新关卡进度，这里假设使用UserDefault保存了关卡进度
    int latestLevel = GameDataManager::getLevelProgress();
    if (latestLevel > 2) {
        GameDataManager::saveLevelProgress(1);//储存当前关卡进度为1
        Director::getInstance()->replaceScene(PromptScene::createScene());
        return;
    }
    // 进入对应的最新游戏场景
    auto level = Level::createWithLevelNumber(latestLevel);
    // 将 Level 对象添加到场景中
    Director::getInstance()->replaceScene(level);

}

void Main_menu::gotoMarket(Ref* pSender)
{
    //按下开始游戏后转入菜单场景
    Director::getInstance()->replaceScene(Market::createScene());
}


void Main_menu::gotoMiniGame(Ref* pSender)
{
    //按下开始游戏后转入主菜单场景
    Director::getInstance()->replaceScene(MiniGame::createScene());
}

void Main_menu::gotoAchievement(Ref* pSender)
{
    //按下开始游戏后转入成就场景
    Director::getInstance()->replaceScene(AchievementScene::createScene());
}