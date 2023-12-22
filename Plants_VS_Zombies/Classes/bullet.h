#pragma once
#include "cocos2d.h"
#include "Entity.h"
class Bullet : public Entity{
public:
    Bullet(int startX, int startY, int bulletDamage, Scene* scene);
    void explodeAnimation();
    void onAnimationFinished(Node* sender);//�ӵ���Ҫ����ʱ���ã���god���ݡ����ӵ������˳�vector�����ź�
    bool NeedRemove(){return needDestroy;}

private:
    int start_x;//�ӵ�����λ��
    int start_y;
    int damage;//�ӵ��˺�
    Scene* currentScene;//��¼�ӵ����ڳ�����ָ��
    int needDestroy;//���ӵ��ɳ���Ļ �����ӵ����н�ʬ�󣬻ᱻ��Ϊ1

    float bulletSpeed;//�ӵ��ٶ�
};