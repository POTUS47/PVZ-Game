#include "Main_menu.h"
#include "SimpleAudioEngine.h"
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //1：结束按钮
   /* auto closeItem = MenuItemImage::create(
        "zombietest.png",
        "zombietest.png",
        CC_CALLBACK_1(Main_menu::menuCloseCallback, this));
    ////////////////修改退出框按钮图片
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
        ////////////修改退出框按钮的相对位置
    }
    //基于第一个退出按钮，我们创建菜单menu
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    */
    // 添加主界面图片（以精灵形式）
    auto sprite = Sprite::create("/main_menu/background.png");
    ////////修改主菜单界面的图片
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
        "/main_menu/adventure2.png", CC_CALLBACK_1(Main_menu::menuCloseCallback, this)
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
        float x = origin.x + visibleSize.width /2*3;
        float y = origin.y + visibleSize.height / 2;
        adventure_mode->setPosition(Vec2(x, y));
        ////////////修改冒险模式按钮的相对位置
    }
    auto menu1 = Menu::create(adventure_mode, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    //3.玩玩小游戏按钮
   /* auto mini_game_mode = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [](cocos2d::Ref* sender) {
            auto mini_game_menu = mini_game_menu::create();
            cocos2d::Director::getInstance()->replaceScene(mini_game_menu);
        }
        );////////////////此处需要调用一个进入小游戏模式场景的函数，记得修改按钮图片

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
        ////////////修改小游戏模式按钮的相对位置
    }
    */
    //4.商店按钮
    /*auto market = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [](cocos2d::Ref* sender) {
            auto Market = Market::create();
            cocos2d::Director::getInstance()->replaceScene(Market);
        }
        );////////////////////////////此处需要调用一个进入商店场景的函数，记得修改按钮图片

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
        ////////////修改小游戏模式按钮的相对位置
    }
    */

    // 按钮回调函数
    /*void startGameCallback(Ref * pSender)
    {
        // 获取最新关卡进度，这里假设使用UserDefault保存了关卡进度
        int latestLevel = UserDefault::getInstance()->getIntegerForKey("LatestLevel", 1);

        // 创建对应的游戏场景
        auto gameScene = GameScene::createScene(latestLevel);

        // 切换场景
        Director::getInstance()->replaceScene(gameScene);
    }
    return true;
    */
}

//菜单按钮1：结束按钮的回调函数
void Main_menu::menuCloseCallback(Ref* pSender)
{
    //退出游戏
    Director::getInstance()->end();
}
//其他按钮的回调函数并没有单独给出，而是直接用匿名函数嵌套到了creat的参数列表中。
