#include"MiniGameLevel.h"

bool MiniGameLevel::initWithLevelNumber(int levelNumber) {

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    if (levelNum == 1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/Level1.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Level1.mp3");
    }
    else if (levelNum == 2) {
        /////////////////////////////待添加
    }

    // 在这里进行场景的初始化，可以根据 levelNumber 做不同的处理
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 1;
    else if (levelNumber == 2) {
        //其他小游戏待添加
    }
    god = new God(isNight, this, levelNumber,1);//1代表是小游戏，不需要储存关卡
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

MiniGameLevel* MiniGameLevel::createWithLevelNumber(int levelNumber) {

    MiniGameLevel* miniLevel = new MiniGameLevel();// 创建 Level 对象

    // 调用 initWithLevelNumber 进行初始化
    if (miniLevel && miniLevel->initWithLevelNumber(levelNumber)) {
        // 自动调用 retain()，由 autorelease() 来释放
        miniLevel->autorelease();
        return miniLevel;
    }
    else {
        // 初始化失败，手动释放内存
        CC_SAFE_DELETE(miniLevel);
        return nullptr;
    }
}

void MiniGameLevel::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //场景要素-------------------------------------------------------------------------------------
    //创建种子雨（这里用sun实现）//
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

void MiniGameLevel::setBackground() {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (levelNum == 1)
        background = Sprite::create("/level/3.png");
    else if (levelNum == 2) {

    }//////其他迷你游戏关卡
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);
}

void MiniGameLevel::update(float dt)
{
    god->randomCardInit(sun);
}

void MiniGameLevel::onMoveByFinished()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //生成僵尸
    god->updateZombies(levelNum);
   
    // 创建延迟动作
    auto delay = cocos2d::DelayTime::create(2.0f);
    // 创建回调动作
    auto callbackMoveRight = [this]() {
        moveRight(NULL);
    };
    auto callback = cocos2d::CallFunc::create(callbackMoveRight);
    // 创建动作序列
    auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);
    // 执行动作序列
    this->runAction(sequence);
}
