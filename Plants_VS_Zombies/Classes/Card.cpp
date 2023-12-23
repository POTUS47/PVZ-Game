#include"Card.h"
#include"plant.h"
#include"PeaShooter.h"

Card::Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*scene) {
    // ʹ�ô����ͼƬ·������ Sprite ����
    Sprite* card = Sprite::create(imagePath);
    setIdv(card);
	plantPath = plantpath;//�����Ӧֲ���ͼƬ·��
	
    // ����λ�ú�����
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    scene->addChild(card,2);
	exaplant = Sprite::create(plantpath);
	exaplant->setPosition(200,200);
	scene->addChild(exaplant);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();
		
		// �жϵ��λ���Ƿ��ڿ�Ƭ��Χ��
		if (card->getBoundingBox().containsPoint(touchLocation)) {
			// ��Ƭ�����������ֲ��ͼƬ
			
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

