#include"Car.h"

Car::Car(int col, Scene* scene)
{
	Sprite* car = Sprite::create("/car/car.png");
	car->setPosition(50, 200 * col - 40);
	car->setScale(2.0);
	setIdv(car);
	scene->addChild(car, 3);
}

void Car::carRun()
{
	MoveBy* run = MoveBy::create(2, Vec2(10, 0));
	getIdv()->runAction(run);
}