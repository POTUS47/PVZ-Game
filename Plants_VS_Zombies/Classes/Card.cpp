#include"Card.h"
#include"plant.h"
#include"PeaShooter.h"
#include"God.h"
#include<vector>
extern std::vector<Plant*>plants;

Vec2 checkPosition(Vec2 Point);

Card::Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*_scene,int _type) {
    // ʹ�ô����ͼƬ·������ Sprite ����
    Sprite* card = Sprite::create(imagePath);
    setIdv(card);
	plantPath = plantpath;//�����Ӧֲ���ͼƬ·��
	type = _type;//����ֲ������
	scene = _scene;
    // ����λ�ú�����
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    _scene->addChild(card,2);
	
	addListener();
}

void Card::addListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerMouse::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
			canClick = true;
		if (canClick == false)
			return false;
		if (!isFollowingMouse)
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
				if (clickLocation.x <= 150 || clickLocation.x >= 1800 || clickLocation.y <= 100 || clickLocation.y >= 1000) {//�������
					;
				}
				else {
					Vec2 real = checkPosition(clickLocation);
					if (real.x == 0 && real.y == 0) {//����õ��Ѿ���ֲ����
						;
					}
					else {
						createPlant(real);
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

//�ȽϴֲڵĹ��λ�ú���
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
		if (row == plants[i]->getRow() && col == plants[i]->getCol()) {
			return Vec2(0, 0);
		}
	}
	return real;
}
//������ֲ��д����Ҫ�������
void Card::createPlant(Vec2 real)
{
	switch (type) {
		case PEASHOOTER:
			plants.push_back(new PeaShooter(real.x, real.y, 2.2, scene));
			break;
		case SUNFLOWER:
			break;
		default:
			break;
	}
}