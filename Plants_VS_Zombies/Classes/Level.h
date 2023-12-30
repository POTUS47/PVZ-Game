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
    int levelNum;//储存当前是何关卡
    God* god; //上帝的实例化
    Sun* sun;
    Sprite* background;//背景的指针
    Layer* choose;//选择植物层的指针
    Label* sunlightLabel;
    bool GameStart = false;//游戏是否开始了？
public:
    // 创建 Level 对象的静态函数，接受一个整数参数
    static Level* createWithLevelNumber(int levelNumber);
    virtual bool initWithLevelNumber(int levelNumber);// 初始化函数
    void setBackground();


    CREATE_FUNC(Level);// 使用宏定义创建 Level 对象

    static cocos2d::Scene* createScene();
    void update(float dt);
    void CheckEveryMin(float dt);
    void goBackMain(cocos2d::Ref* pSender);
    void CheckEveryTwoSec(float dt);
    void moveRight(Ref* sender);//场景和僵尸向右移动


    virtual void onMoveByFinished();//小游戏需要重新写
    virtual void startChoose();//小游戏需要重新写

    //新写的函数

};


/*备注：
* Level类的使用方法：
* Level* level = Level::createWithLevelNumber(levelNumber);
* 不知道能不能auto level= Level::createWithLevelNumber(levelNumber);
// 将 Level 对象添加到场景中
Director::getInstance()->replaceScene(level);
*/