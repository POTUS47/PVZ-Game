#pragma once
#include"cocos2d.h"
#include"Entity.h"

class Card :public Entity
{
public:
	//���캯��������λ�ã���С��ͼƬ·��
	Card(int x, int y, float scale, const std::string& imagePath,Scene*scene);
	//��ӿ�Ƭ������
};
