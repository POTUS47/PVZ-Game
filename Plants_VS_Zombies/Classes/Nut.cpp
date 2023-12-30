#include "Nut.h"

Nut::Nut(int x, int y, double scale, Scene* scene) {
    setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
    setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
    auto nut = cocos2d::Sprite::create("/plant/nut/zz1.png");
    nut->setPosition(x, y);
    nut->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(nut, 2);
    setIdv(nut);//������ָ�����idv

    //��������ֵ������
    setHealth(800);
    //��ֲ�￪ʼҡ��
    waitingAnimation();
}

//ֲ��Ŀ���ҡ�ڶ���
void Nut::waitingAnimation() {

    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        sprintf(nameSize, "/plant/nut/zz%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(INFINITE);//���ö������ŵ�ѭ������ INFINITE��ʾ���޴�
    //animation->setRestoreOriginalFrame(true);����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    this->getIdv()->runAction(animate);//����������Ӧ�õ������ϣ������ж���
}
