#include "Jalapeno.h"

Jalapeno::Jalapeno(int x, int y, double scale, Scene* scene) {
    setRow((y - 160) / 190 + 1);//����ֲ������һ�г���
    setCol((x - 215) / 190 + 1);//����ֲ������һ�г���
    setX(x);
    setY(y);
    setName(PUFF_SHROOM);
    auto jalapeno = cocos2d::Sprite::create("/plant/jalapeno/j (1).png");
    jalapeno->setPosition(x, y);
    jalapeno->setScale(scale);
    //��ӵ���ǰ��
    scene->addChild(jalapeno, 2);
    setIdv(jalapeno);//������ָ�����idv

    //��������ֵ������
    setHealth(100);
    setAttackDamage(1000);
    //��ֲ�￪ʼҡ��
    working();
}

//ֲ��ı�ը����
void Jalapeno::working() {
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/jalapeno/j (%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//�򶯻������һ���ļ�·����Ӧ�ľ���֡
    }
    animation->setDelayPerUnit(0.15f);//����ÿ֡���ŵ�ʱ����
    animation->setLoops(1);//���ö������ŵ�ѭ������
    animation->setRestoreOriginalFrame(true);//����������󶨸��ڵ�һ֡
    auto animate = Animate::create(animation);//������������
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Jalapeno::onAnimationFinished, this));
    auto sequence = Sequence::create(animate, callFunc, nullptr);
    this->getIdv()->runAction(sequence);//����������Ӧ�õ������ϣ������ж���
}


void Jalapeno::onAnimationFinished(Node* sender){
    this->setCondition(BOMB);
}