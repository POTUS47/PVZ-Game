#include "Jalapeno.h"

Jalapeno::Jalapeno(int x, int y, double scale, Scene* scene, int isNight) {
    setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
    setCol((x - 215) / 190 + 1);//设置植物在哪一列出现
    setX(x);
    setY(y);
    setName(PUFF_SHROOM);
    auto jalapeno = cocos2d::Sprite::create("/plant/jalapeno/j(1).png");
    jalapeno->setPosition(x, y);
    jalapeno->setScale(scale);
    //添加到当前层
    scene->addChild(jalapeno, 2);
    setIdv(jalapeno);//将精灵指针存入idv

    //设置生命值等属性
    setHealth(100);
    setAttackDamage(1000);
    //让植物开始摇摆
    working();
}

//植物的爆炸动画
void Jalapeno::working() {
    auto animation = Animation::create();
    char nameSize[30] = { 0 };
    for (int i = 1; i < 15; i++)
    {
        sprintf(nameSize, "/plant/jalapeno/j(%d).png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(1);//设置动画播放的循环次数
    animation->setRestoreOriginalFrame(true);//动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    auto callFunc = CallFuncN::create(CC_CALLBACK_1(Jalapeno::onAnimationFinished, this));
    auto sequence = Sequence::create(animate, callFunc, nullptr);
    this->getIdv()->runAction(sequence);//将动画动作应用到精灵上，并运行动画
}

//植物死亡：消失 注意火爆消失的逻辑在god中通过bomb检测
void Jalapeno::dieAnimation() {
    this->setCondition(DEAD);
    getIdv()->setVisible(false);
    //this->getIdv()->removeFromParent();//让植物立刻消失在画面中
}

void Jalapeno::onAnimationFinished(Node* sender){
    this->setCondition(BOMB);
}