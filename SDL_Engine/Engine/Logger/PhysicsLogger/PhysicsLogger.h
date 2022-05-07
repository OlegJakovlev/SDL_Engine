#pragma once

#ifndef PhysicsLogger_H
#define PhysicsLogger_H

#include "../Logger.h";

class PhysicsLogger : public Logger {
public:
    static PhysicsLogger& Instance();
    void LogMessage(const std::string& msg) override;
    void LogWarning(const std::string& msg) override;
    void LogError(const std::string& msg) override;

private:
    explicit PhysicsLogger(const std::string& newOutputFile = "physics.log");
    PhysicsLogger& operator=(const PhysicsLogger&) = delete;
    PhysicsLogger(const PhysicsLogger&) = delete;
    ~PhysicsLogger() override = default;
};

#endif
