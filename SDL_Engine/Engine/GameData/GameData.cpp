#include "GameData.h"

GameData* GameData::sInstance = nullptr;

GameData::~GameData() {
    data.clear();
}

GameData* GameData::Instance() {
    if (sInstance == nullptr) return new GameData();
    return sInstance;
}

void GameData::Release() {
    delete sInstance;
    sInstance = nullptr;
}
