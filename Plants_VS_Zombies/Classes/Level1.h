#pragma once
#include "cocos2d.h"
#include"God.h"

class Level1 : public cocos2d::Scene
{
private:
    God* god;
    Sprite* background;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void goBackMain(cocos2d::Ref* pSender);
    void onMoveByFinished();
    void update(float dt);
    void moveLeft();//���������ƶ�
    void moveRight();//�����ͽ�ʬ�����ƶ�


    // implement the "static create()" method manually
    CREATE_FUNC(Level1);
};