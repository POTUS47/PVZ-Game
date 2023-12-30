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
#include"User.h"
#include"PromptScene.h"

class God;
class Level : public cocos2d::Scene
{
private:
    int levelNum;//���浱ǰ�Ǻιؿ�
    God* god; //�ϵ۵�ʵ����
    Sun* sun;
    Sprite* background;//������ָ��
    Layer* choose;//ѡ��ֲ����ָ��
    Label* sunlightLabel;
    bool GameStart = false;//��Ϸ�Ƿ�ʼ�ˣ�
public:
    // ���� Level ����ľ�̬����������һ����������
    static Level* createWithLevelNumber(int levelNumber);
    virtual bool initWithLevelNumber(int levelNumber);// ��ʼ������
    void setBackground();


    CREATE_FUNC(Level);// ʹ�ú궨�崴�� Level ����

    static cocos2d::Scene* createScene();
    void update(float dt);
    void CheckEveryMin(float dt);
    void goBackMain(cocos2d::Ref* pSender);
    void CheckEveryTwoSec(float dt);
    void moveRight(Ref* sender);//�����ͽ�ʬ�����ƶ�


    virtual void onMoveByFinished();//С��Ϸ��Ҫ����д
    virtual void startChoose();//С��Ϸ��Ҫ����д

    //��д�ĺ���

};


/*��ע��
* Level���ʹ�÷�����
* Level* level = Level::createWithLevelNumber(levelNumber);
* ��֪���ܲ���auto level= Level::createWithLevelNumber(levelNumber);
// �� Level ������ӵ�������
Director::getInstance()->replaceScene(level);
*/