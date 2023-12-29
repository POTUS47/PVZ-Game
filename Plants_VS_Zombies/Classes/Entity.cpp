#include"cocos2d.h"
#include"Entity.h"
USING_NS_CC;

Sprite* Entity::getIdv()
{
	return idv;
}

void Entity::setIdv(Sprite* _idv)
{
	idv = _idv;
}