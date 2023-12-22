#include"Card.h"

Card::Card(int x, int y, float scale, const std::string& imagePath,Scene*scene) {
    // 使用传入的图片路径创建 Sprite 对象
    Sprite* card = Sprite::create(imagePath);
    setIdv(card);
    // 设置位置和缩放
    card->setPosition(Vec2(x, y));
    card->setScale(scale);
    scene->addChild(card,2);
    //addMouseListener(card);
	// 
	// 
	// 为卡片添加点击事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [card, this](Touch* touch, Event* event) {
		// 获取点击位置
		Point touchLocation = touch->getLocation();

		// 判断点击位置是否在卡片范围内
		if (card->getBoundingBox().containsPoint(touchLocation)) {
			// 卡片被点击，执行消失逻辑
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

	// 启动一个定时器，在五秒后检查是否有鼠标点击阳光，若无则自动消失
	/*float t = (1400 - y) / speed + 5;
	auto delayAction = DelayTime::create(t);
	auto checkClickCallback = CallFunc::create([sun, scene]() {
		if (sun && sun->getParent()) {
			// 阳光还存在且没有被点击，则自动让阳光消失
			sun->removeFromParent();
		}
		});
	auto sequence = Sequence::create(delayAction, checkClickCallback, nullptr);
	sun->runAction(sequence);*/
}

