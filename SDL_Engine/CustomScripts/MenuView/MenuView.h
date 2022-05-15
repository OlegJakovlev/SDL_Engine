#pragma once

#ifndef MenuView_H
#define MenuView_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/TextComponent/TextComponent.h"

class MenuView : public AbstractComponent {
public:
    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;

private:
    TextComponent* titleText;
    TextComponent* engineControlsText;
    TextComponent* gameplayControlsText;

    std::string title;
    std::string engineControls;
    std::string gameControls;
};

#endif