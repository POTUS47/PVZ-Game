#include "Level.h"

extern std::vector<Zombie*>waiting;//考虑把vector变成god的一个内置成员

bool Level::initWithLevelNumber(int levelNumber) {
    // 在这里进行场景的初始化，可以根据 levelNumber 做不同的处理
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 0;
    else if (levelNumber == 2)
        isNight = 1;
    /////////////////////////////////////////////////需要再添加
    god = new God(isNight, this, levelNumber);
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
    else if(levelNum == 2){
        background = Sprite::create("/level/3.jpg");
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

/*在关卡中建立返回菜单的label
#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
    virtual bool init() override {
        if (!Scene::init()) {
            return false;
        }

        // 创建返回按钮的Label
        auto backButtonLabel = cocos2d::Label::createWithTTF("Back to Main Menu", "fonts/arial.ttf", 24);
        auto backButton = cocos2d::MenuItemLabel::create(backButtonLabel, CC_CALLBACK_1(MainMenuScene::menuBackCallback, this));

        backButton->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

        // 创建菜单，并将返回按钮添加到菜单中
        auto menu = cocos2d::Menu::create(backButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu, 1);

        // 启用触摸监听
        auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    // 返回按钮点击事件处理函数
    void menuBackCallback(cocos2d::Ref* pSender) {
        // 切换到主菜单场景
        cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
    }

    // 触摸事件处理函数
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
        // 判断触摸点是否在按钮范围内
        auto target = static_cast<Node*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode)) {
            // 如果触摸点在按钮范围内，执行按钮点击事件处理函数
            menuBackCallback(target);
            return true;
        }
        return false;
    }

    CREATE_FUNC(MainMenuScene);
};

// 在游戏关卡中使用该按钮
// 在你的关卡场景中，通过以下代码创建并添加返回按钮
// auto backToMainMenuLabel = BackToMainMenuLabel::create();
// this->addChild(backToMainMenuLabel);
*/