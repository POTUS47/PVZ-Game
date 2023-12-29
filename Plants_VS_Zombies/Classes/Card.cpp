#include"Card.h"

extern std::vector<Card*>cards;
extern std::vector<Plant*>plants;
extern std::vector<Card*>randCards;
extern bool isNight;
int howMuch(int type);
float setTime(int type);

Card::Card(int x, int y, float scale, const std::string& imagePath, 
	const std::string& plantpath,Scene*_scene,int _type,Sun*_sun,int IsNight) {
	isNight = IsNight;
    // 使用传入的图片路径创建 Sprite 对象
	plantPath = plantpath;//保存对应植物的图片路径
	cardPath = imagePath + ".png";
	waitCardPath= imagePath + "wait.png";
    Sprite* card = Sprite::create(cardPath);
    setIdv(card);
	setCondition(POOR);
	money = howMuch(_type);//设置价钱
	sleepTime = setTime(_type);//设置卡片冷却时间
	sun = _sun;
	
	type = _type;//设置植物类型
	scene = _scene;
    // 设置位置和缩放
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    _scene->addChild(card,2);
	if (type == MINIGAME) {
		addMINIListener();
	}
	else {
		addListener();
	}
}

void Card::addListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerMouse::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		if (type == SHOVEL) {
			canClick = true;
		}
		else {
			int sunmoney = sun->getSunValue();
			if (sunmoney >= getMoney()) {//如果现在的阳光值大于等于这个卡片的价钱
				if (getCondition() == SLEEP) {//如果现在在休眠
					canClick == false;
				}
				else {
					setCondition(ABLE);
					changeApperence(1);
				}
			}
			else {
				setCondition(POOR);
				changeApperence(0);
			}

			if (getCondition() == ABLE) {
				canClick = true;
			}
			else if (getCondition() != ABLE) {
				canClick = false;
			}
		}
		
		if (canClick == false)
			return false;
		if (!isFollowingMouse&&canClick==true)
		{
			Point clickLocation = touch->getLocation();
			if (getIdv()->getBoundingBox().containsPoint(clickLocation)) {
				plantFollowSprite = Sprite::create(plantPath);
				plantFollowSprite->setPosition(clickLocation);
				plantFollowSprite->retain();
				plantFollowSprite->setScale(1.95);
				scene->addChild(plantFollowSprite,4);
				isFollowingMouse = true;
				return true;
			}
		}
		else
		{
			Point clickLocation = touch->getLocation();
			if (isFollowingMouse == true)
			{
				isFollowingMouse = false;
				if (clickLocation.x <= 150 || clickLocation.x >= 1800 || clickLocation.y <= 100 || clickLocation.y >= 1000) {//如果出界
					;
				}
				else {
					Vec2 real = checkPosition(clickLocation);
					if (real.x == 0 && real.y == 0) {//如果该点已经有植物了
						if (type == SHOVEL) {
							for (int i = 0; i < plants.size(); i++) {
								cocos2d::Rect boundingBox = plants[i]->getIdv()->getBoundingBox();
								if (boundingBox.containsPoint(clickLocation)) {
									plants[i]->setCondition(DEAD);
									plants[i]->getIdv()->setVisible(false);
								}
							}
						}
					}
					else {
						
							createPlant(real);
							int currentSun = sun->getSunValue();
							int minus = getMoney();
							sun->setSunValue(currentSun -= minus);
							sun->updateSun();
							auto delay = DelayTime::create(sleepTime);/////////////////////////////////////////此处有问题，不恢复了
							condition = SLEEP;
							changeApperence(0);
							getIdv()->setTexture(waitCardPath);
							auto sequence = Sequence::create(delay, CallFunc::create([=]() {
								condition = POOR; // 解除休眠
								}), nullptr);
							getIdv()->runAction(sequence);
						
					}
				}
				plantFollowSprite->removeFromParent();
			}
		}
		return false;
	};
	listener1->onMouseMove = [=](Event* event)
	{
		if (isFollowingMouse)
		{
			EventMouse* e = (EventMouse*)event;
			plantFollowSprite->setPosition(Point(e->getCursorX(), e->getCursorY()));
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, getIdv());
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, getIdv());
}

void Card::addMINIListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerMouse::create();
	
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		canClick = true;
		
		if (canClick == false)
			return false;
		if (!isFollowingMouse && canClick == true)
		{
			int randplant = rand() % 7 + 1;
			switch (randplant) {
				case 1:
					plantPath = "/plant/peashooter/Peashooter1.png";
					type = PEASHOOTER;
					break;
				case 2:
					plantPath = "/plant/sunflower/SunFlower1.png";
					type = SUNFLOWER;
					break;
				case 3:
					plantPath = "/plant/nut/zz1.png";
					type = NUT;
					break;
				case 4:
					plantPath = "/plant/doubleshooter/Repeater1.png";
					type = DOUBLESHOOTER;
					break;
				case 5:
					plantPath = "/plant/sunshroom/b0.png";
					type = SUN_SHROOM;
					break;
				case 6:
					plantPath = "/plant/jalapeno/j (1).png";
					type = JALAPENO;
					break;
				case 7:
					plantPath = "/plant/fumeshroom/s (1).png";
					type = FUME_SHROOM;
					break;
				case 8:
					plantPath = "/plant/puffshroom/w (1).png";
					type = PUFF_SHROOM;
					break;
			}
			Point clickLocation = touch->getLocation();
			if (getIdv()->getBoundingBox().containsPoint(clickLocation)) {
				plantFollowSprite = Sprite::create(plantPath);
				plantFollowSprite->setPosition(clickLocation);
				plantFollowSprite->retain();
				plantFollowSprite->setScale(1.95);
				scene->addChild(plantFollowSprite, 4);
				isFollowingMouse = true;
				return true;
			}
		}
		else
		{
			Point clickLocation = touch->getLocation();
			if (isFollowingMouse == true)
			{
				isFollowingMouse = false;
				if (clickLocation.x <= 150 || clickLocation.x >= 1800 || clickLocation.y <= 100 || clickLocation.y >= 1000) {//如果出界
					;
				}
				else {
					Vec2 real = checkPosition(clickLocation);
					if (real.x == 0 && real.y == 0) {//如果该点已经有植物了
						;
					}
					else {
						createPlant(real);
						getIdv()->removeFromParent();
					}
				}
				plantFollowSprite->removeFromParent();
			}
		}
		return false;
	};
	listener1->onMouseMove = [=](Event* event)
	{
		if (isFollowingMouse)
		{
			EventMouse* e = (EventMouse*)event;
			plantFollowSprite->setPosition(Point(e->getCursorX(), e->getCursorY()));
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, getIdv());
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, getIdv());
}


//比较粗糙的规格化位置函数
Vec2 checkPosition(Vec2 Point)
{
	Vec2 real;
	int row, col;
	for (int i = 0; i <  9; i ++) {
		if (120 + i * 190 <= Point.x && Point.x <= 120 + (i + 1) * 190) {
			real.x = 215 + i * 190;
			col = i + 1;
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (65 + i * 190 <= Point.y && Point.y <= 65 + (i + 1) * 190) {
			real.y = 160 + i * 190;
			row = i + 1;
			break;
		}
	}
	for (int i = 0; i < plants.size(); i++) {
		if (row == plants[i]->getRow() && col == plants[i]->getCol()&&plants[i]->getCondition()!=DEAD) {
			return Vec2(0, 0);
		}
	}
	return real;
}
//其他的植物写好了要在这里加
void Card::createPlant(Vec2 real)
{
	switch (type) {
		case PEASHOOTER:
			plants.push_back(new PeaShooter(real.x, real.y, 2.2, scene));
			break;
		case SUNFLOWER:
			plants.push_back(new Sunflower(real.x, real.y, 2.2, scene,isNight));//要改成isnight
			break;
		case DOUBLESHOOTER:
			plants.push_back(new DoubleShooter(real.x, real.y, 2.2, scene));
			break;
		case NUT:
			plants.push_back(new Nut(real.x, real.y, 2.2, scene));
			break;
		case SUN_SHROOM:
			plants.push_back(new SunShroom(real.x, real.y, 2.2, scene,isNight));
			break;
		case PUFF_SHROOM:
			plants.push_back(new PuffShroom(real.x, real.y, 2.2, scene, isNight));
			break;
		case FUME_SHROOM:
			plants.push_back(new FumeShroom(real.x, real.y, 2.2, scene, isNight));
			break;
		case JALAPENO:
			plants.push_back(new Jalapeno(real.x, real.y, 2.2, scene));
		default:
			break;
	}
}

int howMuch(int type)
{
	switch (type) {
		case  PEASHOOTER:
			return 100;
		case SUNFLOWER:
			return 50;
		case DOUBLESHOOTER:
			return 200;
		case NUT:
			return 50;
		case SUN_SHROOM:
			return 25;
		case PUFF_SHROOM:
			return 0;
		case FUME_SHROOM:
			return 75;
		case JALAPENO:
			return 125;
		case SHOVEL:
			return 0;
		default:
			break;
	}
}

float setTime(int type)
{
	switch (type) {
		case  PEASHOOTER:
			return 5;
		case SUNFLOWER:
			return 20;
		case DOUBLESHOOTER:
			return 10;
		case NUT:
			return 15;
		case SUN_SHROOM:
			return 7.5;
		case PUFF_SHROOM:
			return 15;
		case FUME_SHROOM:
			return 7.5;
		case JALAPENO:
			return 50;
		case SHOVEL:
			return 0;
		default:
			break;
	}
}

void Card::changeApperence(int kind)
{
	if (kind == 1) {//如果是ABLE
		getIdv()->setTexture(cardPath);
	}
	else if (kind == 0) {
		getIdv()->setTexture(waitCardPath);
	}
}