#include"User.h"

void GameDataManager::saveLevelProgress(int levelNumber) {
    cocos2d::UserDefault::getInstance()->setIntegerForKey("LevelProgress", levelNumber);
    cocos2d::UserDefault::getInstance()->flush();  // ȷ�����ݱ�����д�����
}

int GameDataManager::getLevelProgress() {
    return cocos2d::UserDefault::getInstance()->getIntegerForKey("LevelProgress", 1); // Ĭ��ֵΪ1����ʾ��һ��
}