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

    // ��ʼ���������������������г����ĳ�ʼ������
    virtual bool initWithLevelNumber(int levelNumber);

    void setBackground();

    // ʹ�ú궨�崴�� Level ����
    CREATE_FUNC(Level);

    static cocos2d::Scene* createScene();
    void update(float dt);
    void CheckEveryMin(float dt);
    void goBackMain(cocos2d::Ref* pSender);
    void CheckEveryTwoSec(float dt);

    virtual void onMoveByFinished();//С��Ϸ��Ҫ����д

    void moveRight(Ref* sender);//�����ͽ�ʬ�����ƶ�
    virtual void startChoose();//С��Ϸ��Ҫ����д
};


/*��ע��
* Level���ʹ�÷�����
* Level* level = Level::createWithLevelNumber(levelNumber);
* ��֪���ܲ���auto level= Level::createWithLevelNumber(levelNumber);
// �� Level ������ӵ�������
Director::getInstance()->replaceScene(level);
*/