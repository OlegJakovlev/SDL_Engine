#pragma once

#ifndef IComponent_H
#define IComponent_H

#include <nlohmann/json.hpp>

class IComponent {
    virtual void Init() = 0;
    virtual void Reset() = 0;
    virtual void LoadConfig(const nlohmann::json& config) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif