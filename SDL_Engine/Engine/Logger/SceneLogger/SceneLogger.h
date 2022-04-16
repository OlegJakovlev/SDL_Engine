#pragma once

#ifndef SceneLogger_H
#define SceneLogger_H

#include "../Logger.h";

class SceneLogger : public Logger {
public:
    static SceneLogger& Instance();

private:
    explicit SceneLogger(const std::string& newOutputFile = "scene.log");
    SceneLogger& operator=(const SceneLogger&) = delete;
    SceneLogger(const SceneLogger&) = delete;
    ~SceneLogger() override = default;
};

#endif
