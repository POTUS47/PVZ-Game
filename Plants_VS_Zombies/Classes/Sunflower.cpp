#include "Sunflower.h"


Sunflower::Sunflower(int x, int y, double scale, Scene* scene,int isNight):theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
	setCol((x - 215) / 190 + 1);//设置植物在哪一列出现
	setX(x);
	setY(y);
	setName(SUNFLOWER);
	auto sunflower = cocos2d::Sprite::create("/plant/sunflower/SunFlower1.png");
    sunflower->setPosition(x, y);
    sunflower->setScale(scale);
    //添加到当前层
    scene->addChild(sunflower, 2);
    setIdv(sunflower);//将精灵指针存入idv
    //设置生命值等属性
    setHealth(100);
    //让植物开始摇摆
	if (isNight)
		setCondition(SLEEP);
	waitingAnimation();
}

//植物的空闲摇摆动画
void Sunflower::waitingAnimation() {
    auto animation = Animation::create();
    char nameSize[50] = { 0 };
    for (int i = 1; i < 9; i++)
    {
        sprintf(nameSize, "/plant/sunflower/SunFlower%d.png", i);
        animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
    }
    animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
    animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
    //animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
    auto animate = Animate::create(animation);//创建动画动作
    this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//植物的工作动画：即将产生阳光 变亮
void Sunflower::attackAnimation() {
	this->getIdv()->stopAllActions();
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 1; i < 15; i++)
	{
		sprintf(nameSize, "/plant/sunflower/(%d).png", i);
		animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
	}
	animation->setDelayPerUnit(0.07f);//设置每帧播放的时间间隔
	animation->setLoops(1);//设置动画播放的循环次数 INFINITE表示无限次
	auto animate = Animate::create(animation);//创建动画动作

	auto sequence = Sequence::create(animate, CallFunc::create([=]() {
		waitingAnimation();
		}), nullptr);
	this->getIdv()->runAction(sequence);//将动画动作应用到精灵上，并运行动画
	//亮一会后转回空闲摇荡
	
}

