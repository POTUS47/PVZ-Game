#pragma once
#include "cocos2d.h"

class GameDataManager {
public:
    // ����ؿ�����
    static void saveLevelProgress(int levelNumber);

    // ��ȡ�ؿ�����
    static int getLevelProgress();
};

