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
    //������Ϸ��ʼǰ�Ļ���
    startChoose();
    //��ʼ������
    //��ʼ��������
    //��ʬ׼������
    
    
    //-------------test
    this->schedule(schedule_selector(Level1::update), 5.0f);
    //this->scheduleOnce(schedule_selector(Level1::update), 5.0f);
    
  
    return true;
}

void Level1::startChoose()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����Ҫ��-------------------------------------------------------------------------------------
    //�����̵�
    Sprite* seedbank = Sprite::create("/level1/seedbank.png");
    seedbank->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.92));
    seedbank->setScale(2.64,2.4);
    this->addChild(seedbank, 1);
    //����ֵ
    sunlightLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
    sunlightLabel->setPosition(Vec2(115, 1038));  // ����Label��λ��
    sunlightLabel->setTextColor(Color4B::BLACK);  // ����������ɫΪ��ɫ
    this->addChild(sunlightLabel,2);  // ��Label��ӵ�������
    //����ͼ
    background = Sprite::create("/level1/bg.jpg");
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);
    //����ͼ�ƹ�ȥ
    auto moveBy = MoveBy::create(2, Vec2(-870, 0));
    background->runAction(moveBy);

    // ����һ��CallFunc����������ִ�лص�����,����movebyִ����ɺ�ִ��ʲô
    auto moveByFinishedCallback = CallFunc::create(CC_CALLBACK_0(Level1::onMoveByFinished, this));
    auto sequence = Sequence::create(moveBy, moveByFinishedCallback, nullptr);
    background->runAction(sequence);
}


// ��������ж���һ����Ա������������MoveBy�������ʱִ�еĻص�
void Level1::onMoveByFinished() 
{
    //���ɽ�ʬ
    god->updateZombies(1, this);
    //���ɲ�
    auto transparentLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(transparentLayer);
    choose = transparentLayer;
    // ��������
    auto sprite = Sprite::create("zombietest.png");
    sprite->setPosition(500, 500);
    choose->addChild(sprite);

    // ������ť
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



//������Ϸ��ת�ز˵�����
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
    // �ƶ�����
    background->runAction(moveBack->clone());
    // �ƶ�ÿ����ʬ
    for (int i = 0; i < waiting.size(); i++) {
        (waiting[i]->getIdv())->runAction(moveBack->clone());
    }
    GameStart = true;
    god->setZombieStartTime();
}



//���ƹ�ȥ������̵���layer���˴�����sequence
//layer��ָ��������Ա
//��layer�ص������е���moveback
