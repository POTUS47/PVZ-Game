#pragma once
#include"cocos2d.h"
#include"Entity.h"
#include<string>

class Card :public Entity
{
private:
	bool isPressed;
	std::string plantPath;
	Sprite* exaplant = nullptr;
public:
	//���캯��������λ�ã���С��ͼƬ·��,ֲ��ͼƬ·��
	Card(int x, int y, float scale, const std::string& imagePath, const std::string& plantpath,Scene*scene);
	//��ӿ�Ƭ������
};
