#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class Main_menu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    //�ص�����
    void menuCloseCallback(cocos2d::Ref* pSender);
    void startGameCallback(Ref* pSender);
    void gotoMarket(Ref* pSender);
    void gotoAchievement(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Main_menu);//���κ꣬���ڴ���Main_menu���һ��ʵ��
    void gotoMiniGame(Ref* pSender);//��������С��Ϸ����
};

#endif // __Main_menu_SCENE_H__
