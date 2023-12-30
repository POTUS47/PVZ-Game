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
    //void startGameCallback(Ref* pSender);
    void gotoLevel1(Ref* pSender);
    void gotoMarket(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Main_menu);//���κ꣬���ڴ���Main_menu���һ��ʵ��
    void Main_menu::startGameCallback(Ref* pSender);
    void Main_menu::gotoMiniGame(Ref* pSender);//��������С��Ϸ����
};

#endif // __Main_menu_SCENE_H__
