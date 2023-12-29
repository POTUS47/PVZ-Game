#pragma once
#include "cocos2d.h"
#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(int Row,int startX, int startY, int bulletDamage, Scene* scene): 
        row(row),start_x(startX), start_y(startY), damage(bulletDamage), currentScene(scene), needDestroy(0){}
    void onAnimationFinished(Node* sender) { needDestroy = 1;}
    //子弹需要销毁时调用，给god传递“该子弹可以退出vector”的信号
    bool NeedRemove() { return needDestroy; }
    int getRow() {
        return row;
    }
    void setRow(int _row) {
        row = _row;
    }
    int getDamgeVlue() { return damage; }

    int getX() { return start_x; }
    int getY() { return start_y; }
    virtual void explodeAnimation() {};
    int condition=NOT_USED;//子弹不要重复攻击用
private:
    int start_x;//子弹发射位置
    int start_y;
    int damage;//子弹伤害
    Scene* currentScene;//记录子弹所在场景的指针
    int needDestroy;//当子弹飞出屏幕 或者子弹击中僵尸后，会被置为1
    int row;//子弹所属行（判断是否与僵尸相撞需要）
};