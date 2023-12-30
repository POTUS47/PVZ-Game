#include "Level.h"

extern std::vector<Zombie*>waiting;//���ǰ�vector���god��һ�����ó�Ա

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
   
    // ��������г����ĳ�ʼ�������Ը��� levelNumber ����ͬ�Ĵ���
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 0;
    else if (levelNumber == 2)
        isNight = 1;
    else if (levelNumber == 3) {
        GameDataManager::saveLevelProgress(1);//���浱ǰ�ؿ�����
        auto newScene = PromptScene::create(); // �滻����ʾ����
        Director::getInstance()->replaceScene(newScene);
        return 1;
    }
    /////////////////////////////////////////////////��Ҫ�����С��Ϸ
    god = new God(isNight, this, levelNumber,0);
    if (!Scene::init())
    {
        return false;
    }
    //������Ϸ��ʼǰ�Ļ���
    startChoose();
    //��ʼ������
    //��ʼ��������
    //��ʬ׼������
    // ���س�ʼ�����
        // ���� Label
    auto label = Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 24);
    // ���� Label ��λ��
    label->setPosition(1800, 1180);
    // �� Label ��ӵ�������
    this->addChild(label);

    // ��Ӵ����¼�������
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // ���ô����¼��ص�����
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // �ڵ�� Label ������ʱִ�з������˵��Ĳ���
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // �������¼���������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);

    return true;
    return true;
}

Level* Level::createWithLevelNumber(int levelNumber) {
    
    Level* level = new Level();// ���� Level ����

    // ���� initWithLevelNumber ���г�ʼ��
    if (level && level->initWithLevelNumber(levelNumber)) {
        // �Զ����� retain()���� autorelease() ���ͷ�
        level->autorelease();
        return level;
    }
    else {
        // ��ʼ��ʧ�ܣ��ֶ��ͷ��ڴ�
        CC_SAFE_DELETE(level);
        return nullptr;
    }
}

void Level::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����Ҫ��-------------------------------------------------------------------------------------
    //�����̵�
    Sprite* seedbank = Sprite::create("/level1/seedbank.png");
    seedbank->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.92));
    seedbank->setScale(2.64, 2.4);
    this->addChild(seedbank, 1);
    //���ӱ���
    Sprite* shovelback = Sprite::create("/level1/shovelback.png");
    shovelback->setPosition(Vec2(visibleSize.width * 0.62, visibleSize.height * 0.92));
    shovelback->setScale(2.2);
    this->addChild(shovelback, 1);
    //����ֵ///////////////////////////////////////////////////////
    sun = new Sun(this);
    god->setSun(sun);
    //����ͼ
    setBackground();

    //����ͼ�ƹ�ȥ
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);

    // ����һ��CallFunc����������ִ�лص�����,����movebyִ����ɺ�ִ��ʲô
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
    }//////�����ؿ�
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);
}

//������MoveBy�������ʱִ�еĻص�
void Level::onMoveByFinished()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    //���ɽ�ʬ
    god->updateZombies(levelNum);
    //���ɲ�
    auto transparentLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(transparentLayer);
    choose = transparentLayer;
    //��������ѡ����
    auto seedchooser = Sprite::create("/level1/seedchooser.png");
    seedchooser->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.43));
    seedchooser->setScale(0.9, 0.77);
    choose->addChild(seedchooser);
    god->showCardinSeedBank(this, sun);

    // ������ť
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

//������Ϸ��ת�ز˵�����
void Level::goBackMain(Ref* pSender)
{
    god->cleanup();
    Director::getInstance()->replaceScene(Main_menu::createScene());
}


void Level::moveRight(Ref* sender)
{
    this->removeChild(choose);

    auto moveBack = MoveBy::create(1, Vec2(620, 0));
    // �ƶ�����
    background->runAction(moveBack->clone());
    // �ƶ�ÿ����ʬ
    for (int i = 0; i < waiting.size(); i++) {
        (waiting[i]->getIdv())->runAction(moveBack->clone());
    }
    GameStart = true;
    god->setZombieStartTime();
    //god->initCar(this);
    update(0);//���ֶ�����һ��
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
