#include"User.h"

void GameDataManager::saveLevelProgress(int levelNumber) {
    cocos2d::UserDefault::getInstance()->setIntegerForKey("LevelProgress", levelNumber);
    cocos2d::UserDefault::getInstance()->flush();  // 确保数据被立即写入磁盘
}

int GameDataManager::getLevelProgress() {
    return cocos2d::UserDefault::getInstance()->getIntegerForKey("LevelProgress", 1); // 默认值为1，表示第一关
}