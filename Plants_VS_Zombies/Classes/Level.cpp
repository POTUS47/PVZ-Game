#include "Level.h"

extern std::vector<Zombie*>waiting;//考虑把vector变成god的一个内置成员

bool Level::initWithLevelNumber(int levelNumber) {
    // 在这里进行场景的初始化，可以根据 levelNumber 做不同的处理
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    god = new God(0, this);
    if (!Scene::init())
    {
        return false;
    }
    //进行游戏开始前的画面
    startChoose();
    //开始进度条
    //开始生成阳光
    //僵尸准备出发
    // 返回初始化结果
    return true;
}

Level* Level::createWithLevelNumber(int levelNumber) {
    
    Level* level = new Level();// 创建 Level 对象

    // 调用 initWithLevelNumber 进行初始化
    if (level && level->initWithLevelNumber(levelNumber)) {
        // 自动调用 retain()，由 autorelease() 来释放
        level->autorelease();
        return level;
    }
    else {
        // 初始化失败，手动释放内存
        CC_SAFE_DELETE(level);
        return nullptr;
    }
}

void Level::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //场景要素-------------------------------------------------------------------------------------
    //种子商店
    Sprite* seedbank = Sprite::create("/level1/seedbank.png");
    seedbank->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.92));
    seedbank->setScale(2.64, 2.4);
    this->addChild(seedbank, 1);
    //铲子背景
    Sprite* shovelback = Sprite::create("/level1/shovelback.png");
    shovelback->setPosition(Vec2(visibleSize.width * 0.62, visibleSize.height * 0.92));
    shovelback->setScale(2.2);
    this->addChild(shovelback, 1);
    //阳光值///////////////////////////////////////////////////////
    sun = new Sun(this);
    god->setSun(sun);
    //背景图
    setBackground();

    //背景图移过去
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);

    // 创建一个CallFunc动作，用于执行回调函数,即在moveby执行完成后执行什么
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level::onMoveByFinished, this));
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback, nullptr);
    background->runAction(sequence);
}

void Level::setBackground() {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (levelNum == 1)
        background = Sprite::create("/level1/bg.jpg");
    else {

    }//////其他关卡
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);
}

//用于在MoveBy动作完成时执行的回调
void Level::onMoveByFinished()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //生成僵尸
    god->updateZombies(levelNum);
    //生成层
    auto transparentLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(transparentLayer);
    choose = transparentLayer;
    //创建种子选择器
    auto seedchooser = Sprite::create("/level1/seedchooser.png");
    seedchooser->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.43));
    seedchooser->setScale(0.9, 0.77);
    choose->addChild(seedchooser);
    god->showCardinSeedBank(this, sun);

    // 创建按钮
    auto closeButton = MenuItemImage::create(
        "/level1/menu.png",
        "/level1/menu.png",
        CC_CALLBACK_1(Level::moveRight, this));

    closeButton->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.1));
    closeButton->setScale(2.0);
    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    choose->addChild(menu);
}

void Level::update(float dt)
{
    sun->createSun();
}

//按下游戏后转回菜单场景
void Level::goBackMain(Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}


void Level::moveRight(Ref* sender)
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
    this->schedule(schedule_selector(Level::update), 7.0f);
    this->schedule(schedule_selector(Level::CheckEveryMin), 0.1f);
    this->schedule(schedule_selector(Level::CheckEveryTwoSec), 2.0f);


}

void Level::CheckEveryMin(float dt)
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
    god->sunShroomGrowUp();
}

void Level::CheckEveryTwoSec(float dt)
{
    god->checkAttack();
}

void Level::Win() {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //戴夫
    auto sprite = Sprite::create("/market/dave.png");

    sprite->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y));
    sprite->setScale(2.5);
    ->addChild(sprite, 0);

    //---------------------------------------------------------------------------------
    //返回菜单的按钮
    auto back = MenuItemImage::create(
        "/market/backbutton1.png", "/market/backbutton2.png",
        CC_CALLBACK_1(Market::goBackMain, this)
    );////////////////////////////此处需要调用一个进入商店场景的函数，记得修改按钮图片

    float x = origin.x + visibleSize.width * 0.55;
    float y = origin.y + visibleSize.height * 0.2;
    back->setPosition(Vec2(x, y));
    back->setScale(2.0);



    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);
}