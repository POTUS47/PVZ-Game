#include "achievement.h"
#include"User.h"
#include<string>
USING_NS_CC;

Scene* AchievementScene::createScene()
{
    return AchievementScene::create();
}

bool AchievementScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //��ȡ��������Χ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��������ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����ͼ
    std::string t9t = "/main_menu/chooseminigame.png";
    auto sprite1 = Sprite::create(t9t);
    sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite1->setScale(2.26);
    this->addChild(sprite1, 1);

    // ���� Label
    auto label = Label::createWithTTF("Click here Back to Menu", "fonts/Marker Felt.ttf", 74);
    label->setPosition(900, 200);
    label->setTextColor(Color4B::BLACK);  // ����������ɫΪ��ɫ
    this->addChild(label, 7);

    //��ǰ�ؿ�����///////////////////////////////////////////��֪��Ϊɶ��ʾ������
    int latestLevel = GameDataManager::getLevelProgress();
    std::string s = "��Ϸ��������" + std::to_string(latestLevel) + "��";
    auto label2 = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 54);
    label2->setPosition(1100, 800);
    label2->setTextColor(Color4B::BLACK);  // ����������ɫΪ��ɫ
    this->addChild(label2, 8);

    //��ͼ
    auto sprite2 = Sprite::create("/main_menu/3.png");
    sprite2->setPosition(400,800);
    sprite2->setScale(0.2);
    this->addChild(sprite2, 1);

    // ��Ӵ����¼�������
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // ���ô����¼��ص�����
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (label->getBoundingBox().containsPoint(touch->getLocation())) {
            // �ڵ�� Label ������ʱִ�з������˵��Ĳ���
            Director::getInstance()->replaceScene(Main_menu::createScene());
            return true;
        }
        return false;
    };

    // �������¼���������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, label);
    return true;

}


void AchievementScene::backtoMain(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(Main_menu::createScene());
}