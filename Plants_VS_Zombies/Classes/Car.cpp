#include"Car.h"

Car::Car(int col, Scene* scene)
{
	setRow(col);
	Sprite* car = Sprite::create("/car/car.png");
	car->setPosition(50, 200 * col - 40);
	car->setScale(2.0);
	setIdv(car);
	setCondition(NOTUSED);
	scene->addChild(car, 3);
}

void Car::carRun()
{
	MoveBy* run = MoveBy::create(3, Vec2(2500, 0));
	getIdv()->runAction(run);
}