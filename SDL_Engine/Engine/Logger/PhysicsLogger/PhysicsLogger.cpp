#include "PhysicsLogger.h"

PhysicsLogger::PhysicsLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

PhysicsLogger& PhysicsLogger::Instance() {
    PhysicsLogger* instance = new PhysicsLogger();
    return *instance;
}

void PhysicsLogger::LogMessage(const std::string& msg) {
    Write("[PHYSICS][MESSAGE] " + msg);
}

void PhysicsLogger::LogWarning(const std::string& msg) {
    Write("[PHYSICS][WARNING] " + msg);
}

void PhysicsLogger::LogError(const std::string& msg) {
    Write("[PHYSICS][*ERROR*] " + msg);
}