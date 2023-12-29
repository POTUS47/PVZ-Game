#pragma once
#include "cocos2d.h"
#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(int Row,int startX, int startY, int bulletDamage, Scene* scene): 
        row(row),start_x(startX), start_y(startY), damage(bulletDamage), currentScene(scene), needDestroy(0){}
    void onAnimationFinished(Node* sender) { needDestroy = 1;}
    //�ӵ���Ҫ����ʱ���ã���god���ݡ����ӵ������˳�vector�����ź�
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
    int condition=NOT_USED;//�ӵ���Ҫ�ظ�������
private:
    int start_x;//�ӵ�����λ��
    int start_y;
    int damage;//�ӵ��˺�
    Scene* currentScene;//��¼�ӵ����ڳ�����ָ��
    int needDestroy;//���ӵ��ɳ���Ļ �����ӵ����н�ʬ�󣬻ᱻ��Ϊ1
    int row;//�ӵ������У��ж��Ƿ��뽩ʬ��ײ��Ҫ��
};