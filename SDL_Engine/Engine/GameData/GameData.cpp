#include "GameData.h"

GameData* GameData::sInstance = nullptr;

GameData::~GameData() {
    data.clear();
}

GameData* GameData::Instance() {
    if (sInstance == nullptr) sInstance = new GameData();
    return sInstance;
}

void GameData::Release() {
    delete sInstance;
    sInstance = nullptr;
}

const std::string& GameData::GetDataEntry(const std::string& key) {
    if (data.find(key) != data.end()) return data.at(key);
    return "";
}

void GameData::AddDataEntry(const std::string& key, const std::string& value) {
    data.emplace(std::make_pair(key, value));
}

void GameData::ReplaceDataEntry(const std::string& key, const std::string& newValue) {
    if (GetDataEntry(key) == "") return;
    data.at(key) = newValue;
}
