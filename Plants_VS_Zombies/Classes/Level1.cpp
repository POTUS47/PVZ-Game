#include "Level1.h"

extern std::vector<Zombie*>waiting;


Scene* Level1::createScene()
{
    return Level1::create();
}

bool Level1::init()
{
    srand(static_cast<unsigned>(time(0)));
    god = new God(0,this);
    if (!Scene::init())
    {
        return false;
    }
    //进行游戏开始前的画面
    startChoose();
    //开始进度条
    //开始生成阳光
    //僵尸准备出发
    
    return true;
}

void Level1::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //场景要素-------------------------------------------------------------------------------------
    //种子商店
    Sprite* seedbank = Sprite::create("/level1/seedbank.png");
    seedbank->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.92));
    seedbank->setScale(2.64,2.4);
    this->addChild(seedbank, 1);
    //铲子背景
    Sprite* shovelback = Sprite::create("/level1/shovelback.png");
    shovelback->setPosition(Vec2(visibleSize.width * 0.62, visibleSize.height * 0.92));
    shovelback->setScale(2.2);
    this->addChild(shovelback,1);
    //阳光值//////////////////////////////////////////////////////////////////////////////////////////////////////////
    sun = new Sun(this);
    god->setSun(sun);
    //背景图
    background = Sprite::create("/level1/bg.jpg");
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);
    //背景图移过去
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);

    // 创建一个CallFunc动作，用于执行回调函数,即在moveby执行完成后执行什么
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level1::onMoveByFinished, this));
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback, nullptr);
    background->runAction(sequence);
}


// 在你的类中定义一个成员函数，用于在MoveBy动作完成时执行的回调
void Level1::onMoveByFinished() 
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //生成僵尸
    god->updateZombies(1);
    //生成层
    auto transparentLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(transparentLayer);
    choose = transparentLayer;
    //创建种子选择器
    auto seedchooser = Sprite::create("/level1/seedchooser.png");
    seedchooser->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.43));
    seedchooser->setScale(0.9,0.77);
    choose->addChild(seedchooser);
    god->showCardinSeedBank(this,sun);

    // 创建按钮
    auto closeButton = MenuItemImage::create(
        "/level1/menu.png",
        "/level1/menu.png",
        CC_CALLBACK_1(Level1::moveRight, this));

    closeButton->setPosition(Vec2(visibleSize.width*0.3,visibleSize.height*0.1));
    closeButton->setScale(2.0);
    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    choose->addChild(menu);
}

void Level1::update(float dt)
{
    sun->createSun();
}

//按下游戏后转回菜单场景
void Level1::goBackMain(Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}


void Level1::moveRight(Ref* sender) 
{
    this->removeChild(choose);
    
    auto moveBack = MoveBy::create(1, Vec2(620, 0));
    // 移动场景
    background->runAction(moveBack->clone());
    // 移动每个僵尸
    for (int i = 0; i < waiting.size(); i++) {
        (waiting[i]->getIdv())->runAction(moveBack->clone());
    }
    GameStart = true;
    god->setZombieStartTime();
    god->initCar(this);
    update(0);//先手动调用一次
    this->schedule(schedule_selector(Level1::update), 7.0f);
    this->schedule(schedule_selector(Level1::CheckEveryMin), 0.1f);
    this->schedule(schedule_selector(Level1::CheckEveryTwoSec), 2.0f);

    
}

void Level1::CheckEveryMin(float dt)
{
    god->gameEnd();
    god->hitByCar();
    god->checkCrush();
    god->checkEat();
    god->checkBulletToDelete();
    god->dead();
    god->checkJalapenoBomb();
    god->checkSunflower();
    god->checkCard();
}

void Level1::CheckEveryTwoSec(float dt)
{
    god->checkAttack();
}

