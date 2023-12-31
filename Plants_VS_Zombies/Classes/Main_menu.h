#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class Main_menu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    //回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);
    //void startGameCallback(Ref* pSender);
    void gotoLevel1(Ref* pSender);
    void gotoMarket(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Main_menu);//带参宏，用于创建Main_menu类的一个实例
    void Main_menu::startGameCallback(Ref* pSender);
    void Main_menu::GoToWhichScene(int latestLevel);//根据最新进度，进入最新关卡场景
    void Main_menu::gotoMiniGame(Ref* pSender);//进入玩玩小游戏界面
};

#endif // __Main_menu_SCENE_H__
