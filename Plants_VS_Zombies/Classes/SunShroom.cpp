#include "SunShroom.h"


//创造阳光菇
SunShroom::SunShroom(int x, int y, double scale, Scene* scene, int isNight) : theScencePlantIn(scene) {
	setRow((y - 160) / 190 + 1);//设置植物在哪一行出现
	setCol((x - 215) / 190 + 1);//设置植物在哪一列出现
	setX(x);
	setY(y);
	setName (SUN_SHROOM);
	setPlantTime( time(0));//获取阳光菇栽种的时间
	auto sunshroom = cocos2d::Sprite::create("/plant/sunshroom/s1.png");
	sunshroom->setPosition(x, y);
	sunshroom->setScale(scale);
	//添加到当前层
	scene->addChild(sunshroom, 2);
	setIdv(sunshroom);//将精灵指针存入idv
	//设置生命值等属性
	setHealth(100);
	//让植物开始摇摆
	if (!isNight) {
		waitingAnimation();
		setCondition(SLEEP);
	}
	else
		littleAnimation();
}

//植物的睡觉动画
void SunShroom::waitingAnimation() {

	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/s%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
	}
	animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
	animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
	//animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
	auto animate = Animate::create(animation);//创建动画动作
	this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//小阳光菇工作中
void SunShroom::littleAnimation() {
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/l%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
	}
	animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
	animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
	//animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
	auto animate = Animate::create(animation);//创建动画动作
	this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}

//大阳光菇工作中(
void SunShroom::bigAnimation() {
	setAdolescent(0);
	this->getIdv()->stopAllActions();
	setCanCreateSun();
	auto animation = Animation::create();
	char nameSize[50] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		sprintf(nameSize, "/plant/sunshroom/b%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);//向动画中添加一个文件路径对应的精灵帧
	}
	animation->setDelayPerUnit(0.15f);//设置每帧播放的时间间隔
	animation->setLoops(INFINITE);//设置动画播放的循环次数 INFINITE表示无限次
	//animation->setRestoreOriginalFrame(true);动画播放完后定格在第一帧
	auto animate = Animate::create(animation);//创建动画动作
	this->getIdv()->runAction(animate);//将动画动作应用到精灵上，并运行动画
}




void  SunShroom::growUp() {
	bigAnimation();
}
