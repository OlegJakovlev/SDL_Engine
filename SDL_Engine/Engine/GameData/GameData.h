#pragma once

#ifndef GameData_H
#define GameData_H

#include <unordered_map>

class GameData {
public:
    static GameData* Instance();
    static void Release();
    
    const std::string& GetDataEntry(const std::string& key);
    void AddDataEntry(const std::string& key, const std::string& value);
    void ReplaceDataEntry(const std::string& key, const std::string& newValue);

private:
    GameData() = default;
    GameData& operator=(const GameData&) = delete;
    GameData(const GameData&) = delete;
    ~GameData();

    std::unordered_map <std::string, std::string> data;

    static GameData* sInstance;
};

#endif