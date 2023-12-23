#include"Card.h"
#include"plant.h"
#include"PeaShooter.h"

Card::Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*scene) {
    // 使用传入的图片路径创建 Sprite 对象
    Sprite* card = Sprite::create(imagePath);
    setIdv(card);
	plantPath = plantpath;//保存对应植物的图片路径
	
    // 设置位置和缩放
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    scene->addChild(card,2);
	exaplant = Sprite::create(plantpath);
	exaplant->setPosition(200,200);
	scene->addChild(exaplant);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();
		
		// 判断点击位置是否在卡片范围内
		if (card->getBoundingBox().containsPoint(touchLocation)) {
			// 卡片被点击，生成植物图片
			
			card->setPosition(touchLocation);
			this->exaplant->setPosition(touchLocation);
			//scene->addChild(exaplant, 5);
			return true;
		}

		return false;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event) {
	
			Point touchLocation = touch->getLocation();
			exaplant->setPosition(touchLocation);
		
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		Point touchLocation = touch->getLocation();
		exaplant->setVisible(false);
		
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);

}

