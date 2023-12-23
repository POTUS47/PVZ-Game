#pragma once
#include "cocos2d.h"
#include "Entity.h"
class Bullet : public Entity{
public:
    Bullet(int col,int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
    void onAnimationFinished(Node* sender);//子弹需要销毁时调用，给god传递“该子弹可以退出vector”的信号
    bool NeedRemove(){return needDestroy;}
    void setCol(int Col) {
        col = Col;
    }
    int getCol() {
        return col;
    }
    void setSEThp(int sethp) {
        setHP = sethp;
    }
    int getSEThp() {
        return setHP;
    }
private:
    int start_x;//子弹发射位置
    int start_y;
    int damage;//子弹伤害
    Scene* currentScene;//记录子弹所在场景的指针
    int needDestroy;//当子弹飞出屏幕 或者子弹击中僵尸后，会被置为1
    int setHP=0;//初设为0，可以扣血，扣完血后变为1
    int col;//子弹所属行（判断是否与僵尸相撞需要）
    float bulletSpeed;//子弹速度
};