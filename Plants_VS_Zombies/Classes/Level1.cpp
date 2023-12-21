#include "Level1.h"

extern std::vector<Zombie*>waiting;


Scene* Level1::createScene()
{
    return Level1::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level1::init()
{
    srand(static_cast<unsigned>(time(0)));
    god = new God();
    if (!Scene::init())
    {
        return false;
    }
    //进行游戏开始前的画面
    startChoose();
    //开始进度条
    //开始生成阳光
    //僵尸准备出发
    
    
    //-------------test
    this->schedule(schedule_selector(Level1::update), 5.0f);
    //this->scheduleOnce(schedule_selector(Level1::update), 5.0f);
    
  
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
    //阳光值
    sunlightLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
    sunlightLabel->setPosition(Vec2(115, 1038));  // 设置Label的位置
    sunlightLabel->setTextColor(Color4B::BLACK);  // 设置字体颜色为黑色
    this->addChild(sunlightLabel,2);  // 将Label添加到场景中
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
    //生成僵尸
    god->updateZombies(1, this);
    //生成层
    auto transparentLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(transparentLayer);
    choose = transparentLayer;
    // 创建精灵
    auto sprite = Sprite::create("zombietest.png");
    sprite->setPosition(500, 500);
    choose->addChild(sprite);

    // 创建按钮
    auto closeButton = MenuItemImage::create(
        "1.png",
        "2.png",
        CC_CALLBACK_1(Level1::moveRight, this));

    closeButton->setPosition(400, 400);

    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    choose->addChild(menu);
}


void Level1::update(float dt)
{
    //god->updateZombies(1,this);
    god->createSun(this,sunlightLabel);
   
}



//按下游戏后转回菜单场景
void Level1::goBackMain(Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}

void Level1::moveLeft()
{
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);
}

void Level1::moveRight(Ref* sender) 
{
    this->removeChild(choose);
    
    auto moveBack = MoveBy::create(2, Vec2(620, 0));
    // 移动场景
    background->runAction(moveBack->clone());
    // 移动每个僵尸
    for (int i = 0; i < waiting.size(); i++) {
        (waiting[i]->getIdv())->runAction(moveBack->clone());
    }
    GameStart = true;
    god->setZombieStartTime();
}



//先移过去随后立刻弹出layer，此处可用sequence
//layer的指针设成类成员
//在layer回调函数中调用moveback
