#include"MiniGameLevel.h"

bool MiniGameLevel::initWithLevelNumber(int levelNumber) {

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    if (levelNum == 1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/Level1.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Level1.mp3");
    }
    else if (levelNum == 2) {
        /////////////////////////////�����
    }

    // ��������г����ĳ�ʼ�������Ը��� levelNumber ����ͬ�Ĵ���
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 1;
    else if (levelNumber == 2) {
        //����С��Ϸ�����
    }
    god = new God(isNight, this, levelNumber,1);//1������С��Ϸ������Ҫ����ؿ�
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

MiniGameLevel* MiniGameLevel::createWithLevelNumber(int levelNumber) {

    MiniGameLevel* miniLevel = new MiniGameLevel();// ���� Level ����

    // ���� initWithLevelNumber ���г�ʼ��
    if (miniLevel && miniLevel->initWithLevelNumber(levelNumber)) {
        // �Զ����� retain()���� autorelease() ���ͷ�
        miniLevel->autorelease();
        return miniLevel;
    }
    else {
        // ��ʼ��ʧ�ܣ��ֶ��ͷ��ڴ�
        CC_SAFE_DELETE(miniLevel);
        return nullptr;
    }
}

void MiniGameLevel::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����Ҫ��-------------------------------------------------------------------------------------
    //���������꣨������sunʵ�֣�//
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

void MiniGameLevel::setBackground() {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (levelNum == 1)
        background = Sprite::create("/level/3.png");
    else if (levelNum == 2) {

    }//////����������Ϸ�ؿ�
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
    //���ɽ�ʬ
    god->updateZombies(levelNum);
   
    // �����ӳٶ���
    auto delay = cocos2d::DelayTime::create(2.0f);
    // �����ص�����
    auto callbackMoveRight = [this]() {
        moveRight(NULL);
    };
    auto callback = cocos2d::CallFunc::create(callbackMoveRight);
    // ������������
    auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);
    // ִ�ж�������
    this->runAction(sequence);
}
