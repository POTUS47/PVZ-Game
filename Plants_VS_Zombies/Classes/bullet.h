#pragma once
#include "cocos2d.h"
#include "Entity.h"
class Bullet : public Entity{
public:
    Bullet(int col,int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
    void onAnimationFinished(Node* sender);//�ӵ���Ҫ����ʱ���ã���god���ݡ����ӵ������˳�vector�����ź�
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
    int start_x;//�ӵ�����λ��
    int start_y;
    int damage;//�ӵ��˺�
    Scene* currentScene;//��¼�ӵ����ڳ�����ָ��
    int needDestroy;//���ӵ��ɳ���Ļ �����ӵ����н�ʬ�󣬻ᱻ��Ϊ1
    int setHP=0;//����Ϊ0�����Կ�Ѫ������Ѫ���Ϊ1
    int col;//�ӵ������У��ж��Ƿ��뽩ʬ��ײ��Ҫ��
    float bulletSpeed;//�ӵ��ٶ�
};