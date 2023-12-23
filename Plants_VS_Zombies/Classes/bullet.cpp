#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(int col, int startX,int startY,int bulletDamage,Scene* scene)
    : start_x(startX), start_y(startY),damage(bulletDamage),currentScene(scene), needDestroy(0){
    
    setCol(col);
    auto bullet = cocos2d::Sprite::create("/plant/bullet/0.png");
    bullet->setPosition(start_x, start_y);///////////////////
    bullet->setScale(2);
    //添加到当前层
    scene->addChild(bullet, 6);
    setIdv(bullet);//将精灵指针存入idv

    //子弹运动动画
    auto moveBy = MoveBy::create(2.0f, Vec2(1920, 0)); // 1秒内向右水平移动1000个像素
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create(moveBy,CallFunc::create([=]() {
        bullet->removeFromParent(); // 移动完成后移除子弹
        }), callFunc, nullptr);
    bullet->runAction(sequence);
}

//子弹播放爆炸特效并消失
void Bullet::explodeAnimation() {

    Sprite* bullet = this->getIdv();
    bullet->stopAllActions();//停止动作
    bullet->setTexture("/plant/bullet/1.png");
    auto delay = DelayTime::create(0.4f);//子弹暂留零点四秒
    auto removeAction = CallFunc::create([bullet]() {
        bullet->removeFromParent();
        });
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Bullet::onAnimationFinished, this));
    auto sequence = Sequence::create( delay, removeAction,callFunc,nullptr);

    // 执行动作序列
    bullet->runAction(sequence);
    //注意Cocos2d-x 的动作是异步执行的 这个构造函数并不会等待动作播放完成就能执行完毕
}

//通知GOD需要移除子弹
void Bullet::onAnimationFinished(Node* sender) {
    needDestroy = 1;
}