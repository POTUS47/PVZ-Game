#pragma once
#include "cocos2d.h"
#include"God.h"
#include "SimpleAudioEngine.h"
#include "Main_menu.h"
#include"Zombie.h"
#include"NormalZombie.h"
#include <string>
#include<vector>


class God;
class Level1 : public cocos2d::Scene
{
private:
    God* god; //�ϵ۵�ʵ����
    Sprite* background;//������ָ��
    Layer* choose;//ѡ��ֲ����ָ��
    Label* sunlightLabel;
    bool GameStart = false;//��Ϸ�Ƿ�ʼ�ˣ�
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void goBackMain(cocos2d::Ref* pSender);
    void onMoveByFinished();
    void update(float dt);
    void moveRight(Ref* sender);//�����ͽ�ʬ�����ƶ�
    void startChoose();

    CREATE_FUNC(Level1);
};