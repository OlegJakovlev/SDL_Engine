#pragma once

#ifndef GameData_H
#define GameData_H

#include <unordered_map>

struct GameData {
public:
    static GameData* Instance();
    static void Release();

    std::unordered_map <std::string, std::string> data;

private:
    GameData() = default;
    GameData& operator=(const GameData&) = delete;
    GameData(const GameData&) = delete;
    ~GameData();

    static GameData* sInstance;
};

#endif