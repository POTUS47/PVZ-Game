#include "Level.h"

extern std::vector<Zombie*>waiting;//考虑把vector变成god的一个内置成员

bool Level::initWithLevelNumber(int levelNumber) {

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    if (levelNum == 1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/Level1.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Level1.mp3");
    }
    else if (levelNum == 2) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/night.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/night.mp3");
    }
   
    // 在这里进行场景的初始化，可以根据 levelNumber 做不同的处理
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 0;
    else if (levelNumber == 2)
        isNight = 1;
    else if (levelNumber == 3) {
        GameDataManager::saveLevelProgress(1);//储存当前关卡进度
        auto newScene = PromptScene::create(); // 替换成提示场景
        Director::getInstance()->replaceScene(newScene);
        return 1;
    }
    /////////////////////////////////////////////////需要再添加小游戏
    god = new God(isNight, this, levelNumber,0);
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
        // 创建 Label
    auto label = Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 24);
    // 设置 Label 的位置
    label->setPosition(1800, 1180);
    // 将 Label 添加到场景中
    this->addChild(label);

    // 添加触摸事件监听器
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // 设置触摸事件回调函数
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // 在点击 Label 区域内时执行返回主菜单的操作
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // 将触摸事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);

    return true;
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
    else if(levelNum == 2){
        background = Sprite::create("/level/3.png");
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
    god->cleanup();
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
    //god->initCar(this);
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
