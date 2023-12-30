#pragma once
#include "cocos2d.h"

class GameDataManager {
public:
    // 保存关卡进度
    static void saveLevelProgress(int levelNumber);

    // 读取关卡进度
    static int getLevelProgress();
};

