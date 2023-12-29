#pragma once
#include "cocos2d.h"
#include"God.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>
#include<vector>
#include"Sun.h"


class God;
class Level : public cocos2d::Scene
{
private:
    God* god; //�ϵ۵�ʵ����
    Sun* sun;
    Sprite* background;//������ָ��
    Layer* choose;//ѡ��ֲ����ָ��
    Label* sunlightLabel;
    bool GameStart = false;//��Ϸ�Ƿ�ʼ�ˣ�

    //


public:
    virtual void Level::SetBackground()=0;//��ӱ���ͼƬ
    /*ʾ����    background = Sprite::create("/level1/bg.jpg");
    background->setPosition(Vec2(visibleSize.width * 0.73 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(2.47, 2.13);
    this->addChild(background, 0);*/
    virtual bool init();//�������������������ʼ������
    static cocos2d::Scene* createScene();
    void update(float dt);
    void CheckEveryMin(float dt);
    void goBackMain(cocos2d::Ref* pSender);
    void CheckEveryTwoSec(float dt);

    void onMoveByFinished();

    void moveRight(Ref* sender);//�����ͽ�ʬ�����ƶ�
    virtual void startChoose();//һ�㲻��Ҫ����д



    CREATE_FUNC(Level);
};
