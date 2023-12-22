#include"Card.h"

Card::Card(int x, int y, float scale, const std::string& imagePath,Scene*scene) {
    // ʹ�ô����ͼƬ·������ Sprite ����
    Sprite* card = Sprite::create(imagePath);
    setIdv(card);
    // ����λ�ú�����
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    scene->addChild(card,2);
    //addMouseListener(card);
	// 
	// 
	// Ϊ��Ƭ��ӵ���¼�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [card, this](Touch* touch, Event* event) {
		// ��ȡ���λ��
		Point touchLocation = touch->getLocation();

		// �жϵ��λ���Ƿ��ڿ�Ƭ��Χ��
		if (card->getBoundingBox().containsPoint(touchLocation)) {
			// ��Ƭ�������ִ����ʧ�߼�
			auto moveTo = MoveTo::create(0.5, Vec2(120, 1130));
			card->runAction(moveTo);
			auto delayAction = DelayTime::create(0.8f);

			auto checkClickCallback = CallFunc::create([card]() {
				card->removeFromParent();
				});
			auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
			card->runAction(sequence);

			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);

	// ����һ����ʱ��������������Ƿ�����������⣬�������Զ���ʧ
	/*float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// ���⻹������û�б���������Զ���������ʧ
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);*/
}

