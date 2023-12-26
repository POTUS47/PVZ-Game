#include "peaBullet.h"

USING_NS_CC;

peaBullet::peaBullet(int startX,int startY,int bulletDamage,Scene* scene):Bullet(startX, startY, bulletDamage, scene)
{
    setCol(startY);/////////////////////////////////////////ת����ʽ�Բ�ȷ��
    auto bullet = cocos2d::Sprite::create("/plant/bullet/0.png");
    bullet->setPosition(startX, startY);
    bullet->setScale(2);
    //��ӵ���ǰ��
    scene->addChild(bullet, 6);
    setIdv(bullet);//������ָ�����idv

    //�ӵ��˶�����
    auto moveBy = MoveBy::create(2.0f, Vec2(1920, 0)); // 1��������ˮƽ�ƶ�1000������
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create(moveBy,CallFunc::create([=]() {
        bullet->removeFromParent(); // �ƶ���ɺ��Ƴ��ӵ�
        }), callFunc, nullptr);
    bullet->runAction(sequence);
}

//�ӵ����ű�ը��Ч����ʧ
void peaBullet::explodeAnimation() {

    Sprite* bullet = this->getIdv();
    bullet->stopAllActions();//ֹͣ����
    bullet->setTexture("/plant/bullet/1.png");
    auto delay = DelayTime::create(0.1f);//�ӵ��������һ��
    auto removeAction = CallFunc::create([bullet]() {
        bullet->removeFromParent();
        });
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create( delay, removeAction,callFunc,nullptr);

    // ִ�ж�������
    bullet->runAction(sequence);
    //ע��Cocos2d-x �Ķ������첽ִ�е� ������캯��������ȴ�����������ɾ���ִ�����
}
