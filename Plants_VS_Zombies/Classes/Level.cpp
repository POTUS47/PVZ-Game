#include "Level.h"

extern std::vector<Zombie*>waiting;//���ǰ�vector���god��һ�����ó�Ա

bool Level::initWithLevelNumber(int levelNumber) {
    // ��������г����ĳ�ʼ�������Ը��� levelNumber ����ͬ�Ĵ���
    levelNum = levelNumber;
    srand(static_cast<unsigned>(time(0)));
    int isNight;
    if (levelNumber == 1)
        isNight = 0;
    else if (levelNumber == 2)
        isNight = 1;
    /////////////////////////////////////////////////��Ҫ�����
    god = new God(isNight, this, levelNumber);
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
        background = Sprite::create("/level/3.jpg");
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
    god->initCar(this);
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

/*�ڹؿ��н������ز˵���label
#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
    virtual bool init() override {
        if (!Scene::init()) {
            return false;
        }

        // �������ذ�ť��Label
        auto backButtonLabel = cocos2d::Label::createWithTTF("Back to Main Menu", "fonts/arial.ttf", 24);
        auto backButton = cocos2d::MenuItemLabel::create(backButtonLabel, CC_CALLBACK_1(MainMenuScene::menuBackCallback, this));

        backButton->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

        // �����˵����������ذ�ť��ӵ��˵���
        auto menu = cocos2d::Menu::create(backButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu, 1);

        // ���ô�������
        auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    // ���ذ�ť����¼�������
    void menuBackCallback(cocos2d::Ref* pSender) {
        // �л������˵�����
        cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
    }

    // �����¼�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
        // �жϴ������Ƿ��ڰ�ť��Χ��
        auto target = static_cast<Node*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode)) {
            // ����������ڰ�ť��Χ�ڣ�ִ�а�ť����¼�������
            menuBackCallback(target);
            return true;
        }
        return false;
    }

    CREATE_FUNC(MainMenuScene);
};

// ����Ϸ�ؿ���ʹ�øð�ť
// ����Ĺؿ������У�ͨ�����´��봴������ӷ��ذ�ť
// auto backToMainMenuLabel = BackToMainMenuLabel::create();
// this->addChild(backToMainMenuLabel);
*/